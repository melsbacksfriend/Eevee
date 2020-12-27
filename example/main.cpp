/*
    Borealis, a Nintendo Switch UI Library
    Copyright (C) 2019-2020  natinusala
    Copyright (C) 2019  p-sam

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

#include <borealis.hpp>
#include <string>
#include <fstream>

#include "custom_layout_tab.hpp"
#include "sample_installer_page.hpp"
#include "sample_loading_page.hpp"

#include <sav/Sav.hpp>
#include <utils/crypto.hpp>
#include <utils/random.hpp>
#include <pkx/PK8.hpp>
#include <sav/Sav8.hpp>
#include <sav/SavSWSH.hpp>
#include <filesystem>
#include <dirent.h>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <sys/stat.h>
#include <functional>
#include <thread>
#include <chrono>
#include <i18n/i18n_internal.hpp>

std::vector<std::vector<std::string>> namelst(32);

std::unique_ptr<pksm::Sav> save;
std::unique_ptr<pksm::PKX> box1Data[32][30];
std::unique_ptr<pksm::PKX> clipboard;
std::string filepath;
u32 size = 0;
bool CheckIsDir(std::string Path)
{
	struct stat statbuf;
	stat(Path.c_str(), &statbuf);
	return S_ISDIR(statbuf.st_mode);
}

std::vector <dirent> LoadDirs(std::string Path)
{
	std::vector <dirent> Files(0);
	DIR* dir;
	struct dirent* ent;
	dir = opendir(Path.c_str());
	while ((ent = readdir(dir)))
	{
		Files.push_back(*ent);
	}
	closedir(dir);
	return Files;
}

bool CheckFileExists(std::string Path)
{
	struct stat buffer;   
	return (stat (Path.c_str(), &buffer) == 0); 
}

std::string pokeToString(pksm::Species pkmn)
{
	std::ifstream pokelist("romfs:/strings/eng/species.txt");
	if (pokelist.is_open())
	{
		if (pkmn == pksm::Species::None)
		{
			pokelist.close();
			return "(Empty Space)";
		}
		else
		{
			for (int i = 0; i < (int)pkmn; i++)
			{
				pokelist.ignore(256, '\n');
			}
			std::string pokename;
			std::getline(pokelist, pokename, '\n');
			pokelist.close();
			return pokename;
		}
	}
	else
	{
		return "FILE NOT FOUND";
	}
}

std::string toSpriteName(std::string pokemonName)
{
	std::string returnVal = "romfs:/";
	std::size_t found = pokemonName.find(".");
	if (found != std::string::npos)
	{
		pokemonName.erase(pokemonName.begin() + (int)found);
	}
    std::size_t found2 = pokemonName.find("’");
    if (found2 != std::string::npos)
    {
        pokemonName.erase(pokemonName.begin() + (int)found2, pokemonName.end() - 1);
    }
	std::size_t found3 = pokemonName.find("♀");
	if (found3 != std::string::npos)
	{
		pokemonName.replace(pokemonName.begin() + (int)found3, pokemonName.end(), "-f");
	}
	std::size_t found4 = pokemonName.find("♂");
	if (found4 != std::string::npos)
	{
		pokemonName.replace(pokemonName.begin() + (int)found4, pokemonName.end(), "-m");
	}
	std::size_t found5 = pokemonName.find(" ");
	if (found5 != std::string::npos)
	{
		pokemonName.replace(pokemonName.begin() + (int)found5, pokemonName.begin() + (int)found5 + 1, "-");
	}
	std::size_t found6 = pokemonName.find(":");
	if (found6 != std::string::npos)
    {
        pokemonName.erase(pokemonName.begin() + (int)found6);
    }
	std::for_each(pokemonName.begin(), pokemonName.end(), [](char & c) {
        c = ::tolower(c);
    });
    pokemonName += ".jpg";
    returnVal += pokemonName;
    return returnVal;
}

std::vector<std::string> NOTIFICATIONS = {
    "You have cool hair",
    "I like your shoes",
    "borealis is powered by nanovg",
    "The Triforce is an inside job",
    "Pozznx will trigger in one day and twelve hours",
    "Aurora Borealis? At this time of day, at this time of year, in this part of the gaming market, located entirely within your Switch?!",
    "May I see it?",
    "Hmm, Steamed Hams!"
};

int main(int argc, char* argv[])
{
    // Init the app
    brls::Logger::setLogLevel(brls::LogLevel::DEBUG);

    if (!brls::Application::init("Borealis Example App"))
    {
        brls::Logger::error("Unable to init Borealis application");
        return EXIT_FAILURE;
    }

    // Create a sample view
    brls::TabFrame* rootFrame = new brls::TabFrame();
    rootFrame->setTitle("Eevee");
    rootFrame->setIcon(BOREALIS_ASSET("icon/borealis.jpg"));

    brls::List* testList = new brls::List();

	pksm::seedRand(time(0));
    brls::SelectListItem* layerSelectItem = new brls::SelectListItem("Select game", { "Sword", "Shield" });

	if (!CheckFileExists("sdmc:/switch/Eevee.bank"))
	{
		std::ofstream bnkCreate("sdmc:/switch/Eevee.bank", std::ios::binary);
		for (int i = 0; i < 2064000; i++)
		{
			bnkCreate << '\0';
		}
		bnkCreate.close();
	}
	brls::List* bankStorage = new brls::List();
    std::vector<brls::Label*> bankBoxes;
    std::vector<std::vector<std::string>> pokelist(200);
    std::vector<std::vector<brls::ListItem*>> pokelist2(200);
    std::vector<std::vector<std::shared_ptr<pksm::PKX>>> pokegomz(200);
	FILE* bnk = fopen("sdmc:/switch/Eevee.bank", "rb");
	u8* bankData = new u8[2064000];
	u8* tempPokegom = new u8[344];
	fread(bankData, 1, 2064000, bnk);
	fclose(bnk);
	int k = 0;
	for (int i = 0; i < 200; i++)
	{
        bankBoxes.push_back(new brls::Label(brls::LabelStyle::REGULAR, "Bank " + std::to_string(i + 1), true));
        bankStorage->addView(bankBoxes[i]);
		for(int j = 0; j < 30; j++)
		{
			for (int l = 0; l < 344; l++)
			{
				tempPokegom[l] = bankData[k];
				k++;
			}	pokegomz[i].push_back(pksm::PKX::getPKM(pksm::Generation::EIGHT, tempPokegom, false, false));
			pokelist[i].push_back(pokeToString(pokegomz[i][j]->species()));
        
        pokelist2[i].push_back(new brls::ListItem(pokelist[i][j]));
        
        if (pokelist[i][j] != "(Empty Space)" && pokelist[i][j] != "FILE NOT FOUND")
        {
        	pokelist2[i][j]->setThumbnail(toSpriteName(pokelist[i][j]));
        }
        
        bankStorage->addView(pokelist2[i][j]);
        
        pokelist2[i][j]->registerAction("Copy", brls::Key::L, [=]()->bool{
			u8* readData = new u8[344];
			for (int l = 0; l < 344; l++)
			{
				readData[l] = bankData[i + (j * 344) + l];
			}
        	clipboard = pksm::PKX::getPKM(pksm::Generation::EIGHT, readData, true, false);
        	return true;
        });
        pokelist2[i][j]->registerAction("Paste", brls::Key::R, [=]()->bool{
        	clipboard->refreshChecksum();
        	for (int l = 0; l < 344; l++)
        	{
        		bankData[i + (j * 344) + l] = clipboard->rawData()[l];
        	}
        	return true;
        });
        pokelist2[i][j]->registerAction("Dump pkx", brls::Key::Y, [=]()->bool{
    	time_t rawtime;
    	time(&rawtime);
    	std::string dumpName;
        if (pokeToString(pokegomz[i][j]->species()) != "Type: Null")
        {
        	dumpName = pokeToString(pokegomz[i][j]->species()) + "-" + std::to_string(localtime(&rawtime)->tm_year + 1900) + "-" + std::to_string(localtime(&rawtime)->tm_mon + 1) + "-" + std::to_string(localtime(&rawtime)->tm_mday) + "-" + std::to_string(localtime(&rawtime)->tm_hour) + "-" + std::to_string(localtime(&rawtime)->tm_min) + "-" + std::to_string(localtime(&rawtime)->tm_sec) + ".pk8";
        }
        else
        {
        	dumpName = "Type Null-" + std::to_string(localtime(&rawtime)->tm_year + 1900) + "-" + std::to_string(localtime(&rawtime)->tm_mon + 1) + "-" + std::to_string(localtime(&rawtime)->tm_mday) + "-" + std::to_string(localtime(&rawtime)->tm_hour) + "-" + std::to_string(localtime(&rawtime)->tm_min) + "-" + std::to_string(localtime(&rawtime)->tm_sec) + ".pk8";
        }
        FILE* dumpFile = fopen(dumpName.c_str(), "wb");
        fwrite(pokegomz[i][j]->partyClone()->rawData(), 1, 344, dumpFile);
        fclose(dumpFile);
        return true;
        });
        pokelist2[i][j]->registerAction("Delete", brls::Key::X, [=]()->bool{
        	FILE* emptyPkxFile = fopen("romfs:/Empty Space.pk8", "rb");
        	u8* emptyPkxData = new u8[344];
        	fread(emptyPkxData, 1, 344, emptyPkxFile);
        	fclose(emptyPkxFile);
        	std::unique_ptr<pksm::PKX> emptyPkx = pksm::PKX::getPKM(pksm::Generation::EIGHT, emptyPkxData, (size_t)344, false);
        	emptyPkx->refreshChecksum();
        	for (int l = 0; l < 344; l++)
        	{
        		bankData[i + (j * 344) + l] = emptyPkx->rawData()[l];
        	}
        	return true;
        });
		}
	}
	
    brls::Label* testLabel = new brls::Label(brls::LabelStyle::REGULAR, "At least one Checkpoint backup is required.", true);

    
    std::vector<std::string> titles;
    std::vector<std::filesystem::path> paths;
    if (CheckFileExists("sdmc:/switch/Checkpoint/saves/0x0100ABF008968000 0x0100ABF008968000"))
    {
    	titles.push_back("Sword");
    	paths.push_back("sdmc:/switch/Checkpoint/saves/0x0100ABF008968000 0x0100ABF008968000");
	}
	if (CheckFileExists("sdmc:/switch/Checkpoint/saves/0x01008DB008C2C000 0x01008DB008C2C000"))
	{
		titles.push_back("Shield");
		paths.push_back("sdmc:/switch/Checkpoint/saves/0x01008DB008C2C000 0x01008DB008C2C000");
	}
    brls::List* blahbakata = new brls::List();
    brls::LayerView* testLayers = new brls::LayerView();
    std::vector<brls::List*> layerList;
    std::vector<std::vector<brls::ListItem*>> blah(2);
    std::vector<std::vector<dirent>> saves;
    brls::ListItem* saveButton = new brls::ListItem("Save open files");
    saveButton->getClickEvent()->subscribe([=](brls::View* view){
    		save->cryptBoxData(false);
        	save->finishEditing();
        	std::shared_ptr<u8[]> rawSave = save->rawData();
        	FILE* out = fopen(filepath.c_str(), "wb");
        	fseek(out, 0, SEEK_SET);
        	fwrite(rawSave.get(), 1, size, out);
        	fclose(out);
        	FILE* bnkout = fopen("sdmc:/switch/Eevee.bank", "wb");
        	fseek(bnkout, 0, SEEK_SET);
        	fwrite(bankData, 1, 2064000, bnkout);
        	fclose(bnkout);
        });
    for(unsigned long i = 0; i < titles.size(); i++)
    {
    	layerList.push_back(new brls::List());
    }
    for (unsigned long i = 0; i < layerList.size(); i++)
    {
    	layerList[i]->addView(new brls::Header(titles[i], false));
    	saves.push_back(LoadDirs(paths[i].string()));
    	for (unsigned long j = 0; j < saves[i].size(); j++)
		{
			std::string tmpstr = saves[i][j].d_name;
			blah[i].push_back(new brls::ListItem(tmpstr));
		}
		for(unsigned long j = 0; j < blah[i].size(); j++)
		{
			layerList[i]->addView(blah[i][j]);
		}
    	for (unsigned long j = 0; j < blah[i].size(); j++)
    	{
    		blah[i][j]->getClickEvent()->subscribe([=](brls::View* view) {
    			filepath = paths[i].string() + "/" + blah[i][j]->getLabel() + "/main";
    			FILE* in = fopen(filepath.c_str(), "rb");
    			std::shared_ptr<u8[]> saveData = nullptr;
    			if (in)
    			{
    				fseek(in, 0, SEEK_END);
        			size = ftell(in);
        			rewind(in);
    				saveData = std::shared_ptr<u8[]>(new u8[size]);
    				fseek(in, 0, SEEK_SET);
    				fread(saveData.get(), 1, size, in);
        			fclose(in);
    			}
    			save = pksm::Sav::getSave(saveData, size);
        		std::vector<std::vector<brls::ListItem*>> vaporeon(32);
        		std::vector<brls::Label*> boxes;
        		for (int l = 0; l < 32; l++)
        		{
        		boxes.push_back(new brls::Label(brls::LabelStyle::REGULAR, "Box " + std::to_string(l + 1), true));
        		blahbakata->addView(boxes[l]);
    			for (int k = 0; k < 30; k++)
    {
        box1Data[l][k] = save->pkm(l, k);
        save->pkm(l, k)->decrypt();
        box1Data[l][k]->decrypt();
        	namelst[l].push_back(pokeToString(box1Data[l][k]->species()));
        	
        vaporeon[l].push_back(new brls::ListItem(namelst[l][k]));
        if (namelst[l][k] != "(Empty Space)" && pokelist[i][j] != "FILE NOT FOUND")
        {
        	vaporeon[l][k]->setThumbnail(toSpriteName(namelst[l][k]));
        }
        
        blahbakata->addView(vaporeon[l][k]);
        vaporeon[l][k]->registerAction("Copy", brls::Key::L, [=]()->bool{
        	clipboard = save->pkm(l, k)->partyClone();
        	return true;
        });
        vaporeon[l][k]->registerAction("Paste", brls::Key::R, [=]()->bool{
        	clipboard = save->transfer(*clipboard);
        	clipboard->refreshChecksum();
        	save->pkm(*clipboard, l, k, true);
        	save->dex(*clipboard);
        	
        	return true;
        });
        vaporeon[l][k]->registerAction("Dump pkx", brls::Key::Y, [=]()->bool{
    	time_t rawtime;
    	time(&rawtime);
    	std::string dumpName;
        if (pokeToString(box1Data[l][k]->species()) != "Type: Null")
        {
        	dumpName = pokeToString(box1Data[l][k]->species()) + "-" + std::to_string(localtime(&rawtime)->tm_year + 1900) + "-" + std::to_string(localtime(&rawtime)->tm_mon + 1) + "-" + std::to_string(localtime(&rawtime)->tm_mday) + "-" + std::to_string(localtime(&rawtime)->tm_hour) + "-" + std::to_string(localtime(&rawtime)->tm_min) + "-" + std::to_string(localtime(&rawtime)->tm_sec) + ".pk8";
        }
        else
        {
        	dumpName = "Type Null-" + std::to_string(localtime(&rawtime)->tm_year + 1900) + "-" + std::to_string(localtime(&rawtime)->tm_mon + 1) + "-" + std::to_string(localtime(&rawtime)->tm_mday) + "-" + std::to_string(localtime(&rawtime)->tm_hour) + "-" + std::to_string(localtime(&rawtime)->tm_min) + "-" + std::to_string(localtime(&rawtime)->tm_sec) + ".pk8";
        }
        FILE* dumpFile = fopen(dumpName.c_str(), "wb");
        fwrite(save->pkm(l, k)->partyClone()->rawData(), 1, 344, dumpFile);
        fclose(dumpFile);
        return true;
        });
        vaporeon[l][k]->registerAction("Delete", brls::Key::X, [=]()->bool{
        	FILE* emptyPkxFile = fopen("romfs:/Empty Space.pk8", "rb");
        	u8* emptyPkxData = new u8[344];
        	fread(emptyPkxData, 1, 344, emptyPkxFile);
        	fclose(emptyPkxFile);
        	std::unique_ptr<pksm::PKX> emptyPkx = pksm::PKX::getPKM(pksm::Generation::EIGHT, emptyPkxData, (size_t)344, false);
        	emptyPkx = save->transfer(*emptyPkx);
        	emptyPkx->refreshChecksum();
        	save->pkm(*emptyPkx, l, k, true);
        	save->dex(*emptyPkx);
        	
        	return true;
        });
    }
    }
    		});
    	}
    	testLayers->addLayer(layerList[i]);
    }

    layerSelectItem->getValueSelectedEvent()->subscribe([=](size_t selection) {
        testLayers->changeLayer(selection);
    });

    testList->addView(layerSelectItem);
    testList->addView(testLabel);
    testList->addView(saveButton);

    rootFrame->addTab("Game Selector", testList);
    rootFrame->addTab("Save Selector", testLayers);
    rootFrame->addSeparator();
    rootFrame->addTab("Current Save", blahbakata);
    rootFrame->addTab("Bank", bankStorage);

    // Add the root view to the stack
    brls::Application::pushView(rootFrame);

    // Run the app
    while (brls::Application::mainLoop())
        ;

    // Exit
    return EXIT_SUCCESS;
}