/*

		Create by

		##########			  ##########		####		 ##		##		###########		###########
		##		  ##		 ## 	   ##		## ##		 ##		##		##		 ##		##		 ##
		##			##		##			##		##	##		 ##		##		##				##
		##			##		##			##		##	 ##		 ##		##		##				##
		##			##		##			##		##	  ##	 ##		##		##				##
		##			##		##			##		##	   ##	 ##		##		#########		#########
		##			##		##			##		##		##	 ##		##		##				##
		##			##		##			##		##		 ##	 ##		##		##				##
		##		  ##		 ## 	   ##		##		  ## ##		##		##				##
		##########			  ##########		##		   ####		##		##				##

*/


#include "Source.cpp"

int gameStart(Player& player, Map& map, Point& point);
int showStatistic(Player& player, Map& map);

int main()
{
	setlocale(LC_ALL, "ru");
	
	Player doniff("DoNiFF", '$');
	Map map;
	Point point;
	point.generatePoints(map);
	
	gameStart(doniff, map, point);

	return 0;
}

int gameStart(Player &player, Map &map, Point& points)
{
	while (true)
	{
		player.setPlayer(map, points);			// Set the player on a map
		points.setPoints(map);
		map.refresh();					// Refresh the map
		showStatistic(player, map);
		int keycap = _getch();			// Delay
		player.movement(keycap, map);
	}

	return 0;
}

int showStatistic(Player& player, Map& map)
{
	std::cout << "\n\n\n\n";
	std::cout << "\t\tPlayer statistic \n Nickname: " << player.getNickname() << "\n LVL: " << player.getLVL() << "\n Points: " << player.getPoints() << "\n Position to X: " <<
		player.getPositionX() << "\n Position to Y: " << player.getPositionY() << "\n";

	return 0;
}

