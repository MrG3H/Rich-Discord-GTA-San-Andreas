#include "game.h"

Game* pGame;

bool Game::IsAnyMissionActive() {
	return *reinterpret_cast<int*>(0x96ABA0);
}

std::string Game::GetCurrentMission() {
	// 0xA7A974 - times
	// 0x96ABA0 - mission status (on/off)
	if (!pGame->IsAnyMissionActive())
		return "Nenhuma";

	char gxtMissionName[8];
	memcpy(gxtMissionName, (void*)(0xC1B364), 8);

	if (gxtMissionName == "")
		return "Nenhuma";

	if (missionNames[gxtMissionName] == "")
		return "Nenhuma";

	return missionNames[gxtMissionName];
}

std::string Game::GetCurrentZone() {
	const float position_x = *reinterpret_cast<float*>(0xB6F2E4), position_y = *reinterpret_cast<float*>(0xB6F2E8), position_z = *reinterpret_cast<float*>(0x8CCC44);

	for (int i = 0; i < sizeof(zone) / sizeof(zone[0]); i++)
	{
		if (position_x > zone[i].min_x && position_y > zone[i].min_y && position_z > zone[i].min_z && position_x < zone[i].max_x && position_y < zone[i].max_y && position_z < zone[i].max_z)
		{
			return zone[i].zone_name;
		}
	}

	return std::string("San Andreas");
}

float Game::GetProgress() {
	return *reinterpret_cast<float*>(0xA4A61C);
}

bool Game::IsInVehicle() {
	return !!(*reinterpret_cast<int*>(0xBA18FC));
}

int Game::GetVehicleID() {
	//return *reinterpret_cast<int*>(0xB700F0);
	try {
		return *reinterpret_cast<WORD*>(*reinterpret_cast<int*>(0xBA18FC) + 0x22);
	}
	catch (...) {
		return -1;
	}

}

float Game::GetPlayerHealth() {
	//return *reinterpret_cast<int*>(0xB700F0);
	try {
		return *reinterpret_cast<float*>(*reinterpret_cast<int*>(0xB6F5F0) + 0x540);
	}
	catch (...) {
		return 0.0;
	}

}

int Game::GetPassedDays() {
	return *reinterpret_cast<int*>(0xB79038);
}

std::string Game::GetTime() {
	BYTE minutes = *reinterpret_cast<BYTE*>(0xB70152);
	std::string minstr;
	if (minutes < 10) minstr = "0" + std::to_string(minutes);
	else minstr = std::to_string(minutes);
	return std::to_string(*reinterpret_cast<BYTE*>(0xB70153)) + ":" + minstr;
}

int Game::GetCurrentWeapon() {
	return *reinterpret_cast<int*>(0xBAA410);
}

int Game::GetCurrentRadio() {
	return *reinterpret_cast<BYTE*>(0x8CB7A5);
}

bool Game::IsPedExists() {
	return *reinterpret_cast<int*>(0xB6F5F0);
}

int Game::GetPlayerMoney() {
	return *reinterpret_cast<int*>(0xB7CE50);
}

int Game::GetPlayerWantedLevel() {
	return *(int*)0xBAA420;
}

bool Game::IsInCutscene() {
	return *reinterpret_cast<BYTE*>(0xB6F065);
}

std::map <std::string, std::string> missionNames = {
	{"AMBULAE", "Paramédico (Submissão)"},
	{"BCESAR2", "Rei no exílio"},
	{"BCESAR4", "Wu Zi Mu"},
	{"BCOU", "Mensageiro (Submissão)"},
	{"BCRASH1", "Badlands"},
	{"BLOOD", "Arena da Morte (Sub-Missão)"},
    {"BOAT", "Escola de Pilotagem (Barcos)"},
    {"BS", "Escola de Pilotagem (Motos)"},
    {"BURGLAR", "Ladrão (Sub-Missão)"},
    {"CASIN10", "Saint Mark's Bistro"},
    {"CASINO1", "Fender Ketchup"},
    {"CASINO2", "Situação Explosiva"},
    {"CASINO3", "Acabaram-se as Fichas"},
    {"CASINO4", "Don Peyote"},
    {"CASINO5", "Tratamento Intensivo"},
    {"CASINO6", "O Negócio da Carne"},
    {"CASINO7", "Moleza"},
    {"CASINO9", "Queda Livre"},
    {"CAT", "Missões da Catalina"},
    {"CESAR1", "High Stakes, Low Rider"},
    {"COPCAR", "Vigilante (Sub-Missão)"},
    {"CRASH1", "Desejo Ardente"},
    {"CRASH2", "Doberman"},
    {"CRASH3", "Importações Ilegais"},
    {"DOC2", "Madd Dogg"},
    {"DS", "Escola de Pilotagem (Carros)"},
    {"DSERT10", "Geleca Verde"},
    {"DSERT3", "Interdição"},
    {"DSERT4", "Verdant Meadows"},
    {"DSERT5", "Aprendendo a Voar"},
    {"DSERT6", "N.O.E."},
    {"DSERT8", "Projeto Secreto"},
    {"DSERT9", "Clandestino"},
    // {"DUAL", "Videogame"},
    {"FARLIE2", "T-Bone Mendez"},
    {"FARLIE3", "Mike Toreno"},
    {"FARLIE4", "Ran Fa Li"},
    {"FARLIE5", "Isca"},
    {"FIRETRK", "Bombeiro (Sub-Missão)"},
    {"FTRAIN", "Sub-Missão de Carga"},
    {"GARAGE1", "Use Flores em Seu Cabelo"},
    {"GARAGE2", "Desconstrução"},
    // {"GRAV", "Let's Get Ready To Bumble (Video Game)"},
    {"GROVE1", "Batendo no B Dup"},
    {"GROVE2", "Grove Para Sempre"},
    // {"GYM", "Gym"},
    {"HEIST1", "Espionagem Arquitetônica"},
    {"HEIST2", "Exploda a Represa"},
    {"HEIST3", "A Chave Para o Coração Dela"},
    {"HEIST4", "Rodas Policiais"},
    {"HEIST5", "Para o Alto e Avante!"},
    {"HEIST9", "Quebrando o Banco do Caligula's"},
    {"INTRO1", "No Início"},
    {"INTRO2", "Ryder"},
    {"KICKSTT", "Kickstart (Estádio)"},
    {"LAFIN1", "Reunindo as Famílias"},
    {"LAFIN2", "O Sabre Verde"},
    {"LOWR", "Lowrider"},
    {"MAN_1", "Uma Casa nas Colinas"},
    {"MAN_2", "Pássaro Vertical"},
    {"MAN_3", "De Volta ao Lar"},
    {"MAN_5", "Negócios de Matar"},
    // {"OTB", "Inside Track (Horse Race Betting)"},
    {"PIMP", "Cafetinagem (Sub-Missão)"},
    // {"POOL", "Pool (Mini-Game)"},
    {"QUARRY", "Pedreira (Sub-Missão)"},
    {"RACETOR", "Corrida"},
    {"RIOT1", "Rebelião"},
    {"RIOT2", "Los Desperados"},
    {"RIOT4", "Fim da Linha"},
    {"RYDER1", "Invasão Domiciliar"},
    {"RYDER2", "Roubando o Tio Sam"},
    {"RYDER3", "Catalisador"},
    {"SCRASH2", "Trilha de Caracol"},
    // {"SHTR", "Go Go Space Monkey (Video Game)"},
    {"SMOKE1", "OG Loc"},
    {"SMOKE2", "Cachorro Corredor"},
    {"SMOKE3", "No Lado Errado da Linha"},
    {"SMOKE4", "Apenas Negócios"},
    {"STREAL1", "Na Mira"},
    {"STEAL2", "Test Drive"},
    {"STEAL4", "Via Rápida da Alfândega"},
    {"STEAL5", "Perfurações"},
    {"STRAP1", "A Vida é uma Praia"},
    {"STRAP2", "Rimas do Madd Dogg"},
    {"STRAP3", "Problemas de Gerenciamento"},
    {"STRAP4", "Festa em Casa"},
    // {"STUNT", "BMX/NRG-500 (Stunt)"},
    {"SWEET1", "Pichando Território"},
    {"SWEET1B", "Limpando o Bairro"},
    {"SWEET2", "Noves (9mm) e AKs"},
    {"SWEET3", "Drive-Thru"},
    {"SWEET4", "Drive-By"},
    {"SWEET5", "A Garota do Sweet"},
    {"SWEET6", "Cesar Vialpando"},
    {"SWEET7", "Los Sepulcros"},
    {"SYN1", "Oportunidade de Foto"},
    {"SYN2", "Jizzy"},
    {"SYN3", "Batedor"},
    {"SYN4", "Assassino Frio"},
    {"SYN5", "Pier 69"},
    {"SYN6", "O Último Voo de Toreno"},
    {"SYN7", "Yay Ka-Boom-Boom"},
    {"TAXI1", "Taxista (Sub-Missão)"},
    {"TORENO1", "Monster"},
    {"TORENO2", "Sequestro"},
    {"TRU1", "Colheita de Corpos"},
    {"TRU2", "Você está indo para San Fierro?"},
    {"TRUCK", "Caminhoneiro (Sub-Missão)"},
    {"VALET1", "555 Denunciamos"},
    {"VCR1", "Apropriação Indébita"},
    {"VCR2", "Meio-dia em Ponto"},
    {"WUZI1", "Mountain Cloud Boys"},
    {"WUZI2", "Assalto Anfíbio"},
    {"WUZI4", "O Negócio de Da Nang"},
    {"ZERO1", "Ataque Aéreo"},
    {"ZERO2", "Linhas de Suprimento..."},
    {"ZERO3", "Enchendo o Tanque"},
    {"ZERO4", "Exército de Novos Modelos"}
};