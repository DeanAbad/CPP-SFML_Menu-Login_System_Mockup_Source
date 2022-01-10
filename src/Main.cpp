#include <iostream>
#include <string> // For manipulating string e.g. to_string()
#include "Platform/Platform.hpp"

using namespace std;

// Menu Switch
// Same as the one in console app, numbers ranging from 0-7
// Name                             Number
// Main Menu                        0
// BS1MA                            1
// BS2MA                            2
// BS3MA                            3
// BS4MA                            4
// BS5MA                            5 *------
// Info                             6       |
// Account Confirmation (Password)  7 <------
// Student Account                  8

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Status: Success on compiling and linking!\n";
#endif

	// CONST variables
	const sf::Vector2f window_size = sf::Vector2f(800, 600);

	// Instance a window object from a sf::Window class

	// 1st arg 'sf::VideoMode' determines window size
	// 2nd arg is the window title
	// 3rd optional argument: sf::Style where it can be any of the fF:
	// None, Titlebar, Resize, Close, Fullscreen, Default; combination example: 'sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close'
	sf::RenderWindow main_window; // Apparently, this one works compared to the official documentation
	main_window.create(sf::VideoMode(window_size.x, window_size.y), "C++ Menu and Login System", sf::Style::Default);
	main_window.setVerticalSyncEnabled(true); // For aligning framerate with the monitor with vertical display
	main_window.setFramerateLimit(30);
	platform.setIcon(main_window.getSystemHandle());

	// Process events
	sf::Event an_event;

	// Current mouse position
	sf::Vector2f mouse_position_current;

	// For background's texture
	sf::Texture background;
	background.loadFromFile("content\\images\\background\\pexels-faik-akmd-1025469.jpg");

	// For background
	sf::RectangleShape wallpaper;
	wallpaper.setSize(sf::Vector2f(window_size.x, window_size.y));
	wallpaper.setTexture(&background, false); // It starts with '&' as it refers to a pointer of the data being loaded
	wallpaper.setTextureRect(sf::IntRect(100, 100, window_size.x * 6, window_size.y * 6));

	// Margin each side: 20px
	// Therefore, the position is: x = 20, y = 20
	sf::RectangleShape background_board;
	background_board.setSize(sf::Vector2f(window_size.x - 40.0, window_size.y - 40.0));
	background_board.setOutlineColor(sf::Color(13, 71, 161, 50));
	background_board.setOutlineThickness(4);
	background_board.setFillColor(sf::Color(227, 242, 253, 150));
	background_board.setPosition(20, 20);

	sf::Font roboto_regular;
	roboto_regular.loadFromFile("content\\fonts\\Roboto-Regular.ttf");

	sf::Font roboto_light;
	roboto_light.loadFromFile("content\\fonts\\Roboto-Light.ttf");

	sf::Text header1;
	header1.setFont(roboto_regular);
	header1.setString("Asian Institute of Computer Studies (AICS) SY 2021-2022");
	header1.setCharacterSize(20);
	header1.setFillColor(sf::Color(13, 71, 161, 255));
	header1.setStyle(sf::Text::Bold);
	header1.setPosition(160, 43);

	sf::Text header2;
	header2.setFont(roboto_regular);
	header2.setString("C++ Menu and Login System");
	header2.setCharacterSize(20);
	header2.setFillColor(sf::Color(13, 71, 161, 255));
	header2.setStyle(sf::Text::Bold);
	header2.setPosition(160, 73); // Based from previous text's y-coordinate, just add 30px for margin

	sf::Text header3;
	header3.setFont(roboto_regular);
	header3.setString("Main Menu: Sections and Others");
	header3.setCharacterSize(20);
	header3.setFillColor(sf::Color(13, 71, 161, 255));
	header3.setStyle(sf::Text::Bold);
	header3.setPosition(160, 103);

	sf::Texture logo_texture;
	logo_texture.loadFromFile("content\\images\\logo\\AICS_logo.png");

	// Guide for positioning and resizing the logo
	sf::CircleShape logo_circle;
	logo_circle.setRadius(50);
	logo_circle.setTexture(&logo_texture, false);
	logo_circle.setPosition(40, 40);

	sf::RectangleShape pseudoline1;
	pseudoline1.setSize(sf::Vector2f(724, 1));
	pseudoline1.setOutlineColor(sf::Color(13, 71, 161, 100));
	pseudoline1.setOutlineThickness(2);
	pseudoline1.setFillColor(sf::Color(13, 71, 161, 100));
	pseudoline1.setPosition(38, 163);

	sf::RectangleShape pseudoline2;
	pseudoline2.setSize(sf::Vector2f(724, 1));
	pseudoline2.setOutlineColor(sf::Color(13, 71, 161, 100));
	pseudoline2.setOutlineThickness(2);
	pseudoline2.setFillColor(sf::Color(13, 71, 161, 100));
	pseudoline2.setPosition(38, 502);

	sf::Text credits;
	credits.setFont(roboto_light);
	credits.setCharacterSize(12);
	credits.setFillColor(sf::Color::White);
	credits.setOutlineColor(sf::Color(13, 71, 161, 100));
	credits.setOutlineThickness(2);
	credits.setStyle(sf::Text::Bold);
	credits.setString(std::wstring(L"Made by Dean Harold P. Abad with C++ and SFML\n      Free use of background image from Pexels\n          Copyright \u00a9 2021 MumuNiMochii")); // wstring acts like wchar_t were complicated unicodes in Windows are solved and applicable in strings
	credits.setPosition(250, 521);

	sf::RectangleShape mini_board;
	mini_board.setSize(sf::Vector2f(window_size.x - 80, window_size.y - 300));
	mini_board.setOutlineColor(sf::Color(13, 71, 161, 100));
	mini_board.setOutlineThickness(4);
	mini_board.setFillColor(sf::Color(227, 242, 253, 225));
	mini_board.setPosition(40, 183);

	sf::Text instruction;
	instruction.setFont(roboto_regular);
	instruction.setString("Instruction: Enter a character or name of your choice from the following to visit into.");
	instruction.setCharacterSize(12);
	instruction.setStyle(sf::Text::Regular);
	instruction.setFillColor(sf::Color(13, 71, 161, 255));
	instruction.setPosition(55, 198);

	// Serves as the 'input box' of the Choice text
	// Get globalBounds when mouse was focused and display blinking '|' here
	// '|' should be in-between 2 characters, to do that maybe use findCharacterPos - 1
	// To do the blinking, sf::Clock must be used for real-time computer clock
	sf::RectangleShape choice_field; // Margins L & R should be additional 20, so '-120'
	choice_field.setSize(sf::Vector2f(window_size.x - 200.0, 40.0));
	choice_field.setOutlineColor(sf::Color(150, 150, 150, 255));
	choice_field.setOutlineThickness(2);
	choice_field.setPosition(56, 223);
	bool choice_field_highlighted = false;

	sf::RectangleShape choice_enter_button;
	choice_enter_button.setSize(sf::Vector2f(75.0, 40.0));	   // (800 - 600 = 200) - 20px margin
	choice_enter_button.setPosition(window_size.x - 132, 223); // (800 - 130 = 670)
	choice_enter_button.setOutlineColor(sf::Color(150, 150, 150, 255));
	choice_enter_button.setOutlineThickness(2);

	sf::Text choice_enter_button_text;
	choice_enter_button_text.setFont(roboto_light);
	choice_enter_button_text.setString("Enter");
	choice_enter_button_text.setFillColor(sf::Color(13, 71, 161, 255));
	choice_enter_button_text.setCharacterSize(12);
	choice_enter_button_text.setStyle(sf::Text::Regular);
	choice_enter_button_text.setPosition(686, 235);

	// For displaying the keyboard input
	sf::String choice; // String is manipulated in event cases
	sf::Text choice_text;
	choice_text.setFont(roboto_light);
	choice_text.setString("Choice");
	choice_text.setCharacterSize(12);
	choice_text.setPosition(65, 235);

	sf::Text choice_cursor_text;
	choice_cursor_text.setFont(roboto_light);
	choice_cursor_text.setCharacterSize(15);
	choice_cursor_text.setFillColor(sf::Color(13, 71, 161, 255));
	bool choice_cursor_text_shown = false;

	sf::RectangleShape main_menu_list;
	main_menu_list.setSize(sf::Vector2f(684, 170));
	main_menu_list.setOutlineColor(sf::Color(13, 71, 161, 100));
	main_menu_list.setOutlineThickness(4);
	main_menu_list.setPosition(58, 290);

	sf::RectangleShape main_menu_divider_vertical;
	main_menu_divider_vertical.setSize(sf::Vector2f(1, 166));
	main_menu_divider_vertical.setFillColor(sf::Color(13, 71, 161, 100));
	main_menu_divider_vertical.setOutlineColor(sf::Color(13, 71, 161, 100));
	main_menu_divider_vertical.setOutlineThickness(2);
	main_menu_divider_vertical.setPosition(400, 292);

	sf::RectangleShape main_menu_divider_horizontal_1;
	main_menu_divider_horizontal_1.setSize(sf::Vector2f(336, 1));
	main_menu_divider_horizontal_1.setFillColor(sf::Color(13, 71, 161, 100));
	main_menu_divider_horizontal_1.setOutlineColor(sf::Color(13, 71, 161, 100));
	main_menu_divider_horizontal_1.setOutlineThickness(2);
	main_menu_divider_horizontal_1.setPosition(60, 322);

	sf::RectangleShape main_menu_divider_horizontal_2;
	main_menu_divider_horizontal_2.setSize(sf::Vector2f(335, 1));
	main_menu_divider_horizontal_2.setFillColor(sf::Color(13, 71, 161, 100));
	main_menu_divider_horizontal_2.setOutlineColor(sf::Color(13, 71, 161, 100));
	main_menu_divider_horizontal_2.setOutlineThickness(2);
	main_menu_divider_horizontal_2.setPosition(405, 322);

	sf::RectangleShape main_menu_divider_horizontal_3;
	main_menu_divider_horizontal_3.setSize(sf::Vector2f(335, 0)); // Change this per menu for visibility
	main_menu_divider_horizontal_3.setFillColor(sf::Color(13, 71, 161, 100));
	main_menu_divider_horizontal_3.setOutlineColor(sf::Color(13, 71, 161, 100));
	main_menu_divider_horizontal_3.setPosition(405, 429);
	main_menu_divider_horizontal_3.setOutlineThickness(0); // Change this per menu for visibility

	sf::Text header4_1;
	header4_1.setFont(roboto_regular);
	header4_1.setCharacterSize(16);
	header4_1.setFillColor(sf::Color(13, 71, 161, 255));
	header4_1.setStyle(sf::Text::Bold);
	header4_1.setPosition(197, 294);
	header4_1.setString("Sections");

	sf::Text header4_2;
	header4_2.setFont(roboto_regular);
	header4_2.setCharacterSize(16);
	header4_2.setFillColor(sf::Color(13, 71, 161, 255));
	header4_2.setStyle(sf::Text::Bold);
	header4_2.setPosition(549, 294);
	header4_2.setString("Others");

	sf::Text back_text;
	back_text.setFont(roboto_regular);
	back_text.setCharacterSize(14);
	back_text.setFillColor(sf::Color(13, 71, 161, 255));
	back_text.setStyle(sf::Text::Regular);
	back_text.setPosition(549, 437);
	back_text.setString(""); // Remove if is in main menu

	sf::Text list1;
	list1.setFont(roboto_regular);
	list1.setCharacterSize(14);
	list1.setFillColor(sf::Color(13, 71, 161, 255));
	list1.setStyle(sf::Text::Regular);
	list1.setLineSpacing(1.5);
	list1.setPosition(197, 335);
	list1.setString("1. BS1MA\n2. BS2MA\n3. BS3MA\n4. BS4MA\n5. BS5MA");

	sf::Text list2;
	list2.setFont(roboto_regular);
	list2.setCharacterSize(14);
	list2.setFillColor(sf::Color(13, 71, 161, 255));
	list2.setStyle(sf::Text::Regular);
	list2.setLineSpacing(1.5);
	list2.setPosition(549, 335);
	list2.setString("i. Info\nq. Quit");

	sf::Texture id_photo_texture;
	std::string id_photo_texture_path = "";
	sf::RectangleShape id_photo;
	int id_photo_num = 0;
	id_photo_texture_path = "content\\images\\id_photo\\sprite (" + std::to_string(id_photo_num) + ").png";
	id_photo_texture.loadFromFile(id_photo_texture_path);
	id_photo.setTextureRect(sf::Rect(0, 0, 16, 24));
	id_photo.setTexture(&id_photo_texture);
	id_photo.setSize(sf::Vector2f(100, 120));
	id_photo.setOutlineThickness(0);
	id_photo.setPosition(523, 306);

	// Main menu numbers for navigation
	int current_menu, last_menu;
	current_menu = 0;
	last_menu = 0;

	// Student details
	int grade = 0;
	std::string grade_string = "";
	std::string name, username, id, password, completion;
	name = "";
	username = "";
	id = "";
	password = "";
	completion = "";

	sf::Clock clock;
	sf::Time choice_cursor_blink;

	// The window is still inanimate and immovable, and therefore will
	// be moved and interact with by the help of the following.
	// Run the program while the window is open
	while (main_window.isOpen())
	{
		id_photo_texture_path = "content\\images\\id_photo\\sprite (" + std::to_string(id_photo_num) + ").png";
		id_photo_texture.loadFromFile(id_photo_texture_path);
		id_photo.setTextureRect(sf::Rect(0, 0, 16, 24));
		id_photo.setTexture(&id_photo_texture);

		// Change displayed texts when switching menus
		switch (current_menu)
		{
			case 0:
				header3.setString("Main Menu: Sections and Others");
				instruction.setString("Instruction: Enter a character or name of your choice from the following to visit into.");

				header4_1.setPosition(197, 294);
				header4_1.setString("Sections");
				header4_2.setPosition(549, 294);
				header4_2.setString("Others");

				list1.setLineSpacing(1.5);
				list1.setPosition(197, 335);
				list1.setString("1. BS1MA\n2. BS2MA\n3. BS3MA\n4. BS4MA\n5. BS5MA");
				list2.setLineSpacing(1.5);
				list2.setPosition(549, 335);
				list2.setString("i. Info\nq. Quit");

				main_menu_divider_horizontal_3.setSize(sf::Vector2f(335, 0));
				main_menu_divider_horizontal_3.setOutlineThickness(0);
				back_text.setString("");
				break;

			case 1:
				id_photo_num = 0;

				header3.setString("BS1MA Section: Students");
				instruction.setString("Instruction: Enter either username, full name, ID, or number of the student.");

				header4_1.setPosition(201, 294);
				header4_1.setString("Names");
				header4_2.setPosition(561, 294);
				header4_2.setString("IDs");

				list1.setLineSpacing(1.5);
				list1.setPosition(153, 335);
				list1.setString("1. Albao, Melvin James\n2. Consejero, Viviane\n3. Tomas, Aljean Santos");
				list2.setLineSpacing(1.5);
				list2.setPosition(539, 335);
				list2.setString("1. 170781\n2. 180715\n3. 141226");

				main_menu_divider_horizontal_3.setSize(sf::Vector2f(335, 1));
				main_menu_divider_horizontal_3.setOutlineThickness(2);
				back_text.setString("b. Back");
				break;

			case 2:
				header3.setString("BS2MA Section: Students");
				instruction.setString("Instruction: Enter either username, full name, ID, or number of the student.");

				header4_1.setPosition(201, 294);
				header4_1.setString("Names");
				header4_2.setPosition(561, 294);
				header4_2.setString("IDs");

				list1.setLineSpacing(1.5);
				list1.setPosition(153, 335);
				list1.setString("1. Abad, Dean Harold\n2. Domodon, Althea  \n3. Fortes, Jhon Emerson");
				list2.setLineSpacing(1.5);
				list2.setPosition(539, 335);
				list2.setString("1. 210013\n2. 190365\n3. 210001");

				main_menu_divider_horizontal_3.setSize(sf::Vector2f(335, 1));
				main_menu_divider_horizontal_3.setOutlineThickness(2);
				back_text.setString("b. Back");
				break;

			case 3:
				header3.setString("BS3MA Section: Students");
				instruction.setString("Instruction: Enter either username, full name, ID, or number of the student.");

				header4_1.setPosition(201, 294);
				header4_1.setString("Names");
				header4_2.setPosition(561, 294);
				header4_2.setString("IDs");

				list1.setLineSpacing(1.5);
				list1.setPosition(153, 335);
				list1.setString("1. Baclaan, Rocel\n2. Fabella, Joshua\n3. Pulmano, Johnmark");
				list2.setLineSpacing(1.5);
				list2.setPosition(539, 335);
				list2.setString("1. 210041\n2. 210076\n3. 210057");

				main_menu_divider_horizontal_3.setSize(sf::Vector2f(335, 1));
				main_menu_divider_horizontal_3.setOutlineThickness(2);
				back_text.setString("b. Back");
				break;

			case 4:
				header3.setString("BS4MA Section: Students");
				instruction.setString("Instruction: Enter either username, full name, ID, or number of the student.");

				header4_1.setPosition(201, 294);
				header4_1.setString("Names");
				header4_2.setPosition(561, 294);
				header4_2.setString("IDs");

				list1.setLineSpacing(1.5);
				list1.setPosition(153, 335);
				list1.setString("1. Castillo, Dawn Xyly\n2. Nepacena, John Jomar\n3. Villafuerte, Sean");
				list2.setLineSpacing(1.5);
				list2.setPosition(539, 335);
				list2.setString("1. 210089\n2. 210077\n3. 210101");

				main_menu_divider_horizontal_3.setSize(sf::Vector2f(335, 1));
				main_menu_divider_horizontal_3.setOutlineThickness(2);
				back_text.setString("b. Back");
				break;

			case 5:
				header3.setString("BS5MA Section: Students");
				instruction.setString("Instruction: Enter either username, full name, ID, or number of the student.");

				header4_1.setPosition(201, 294);
				header4_1.setString("Names");
				header4_2.setPosition(561, 294);
				header4_2.setString("IDs");

				list1.setLineSpacing(1.5);
				list1.setPosition(153, 335);
				list1.setString("1. Bonavente, Timothy\n2. Latoja, Jiggs Venick\n3. Pasildo, Edmund Paul");
				list2.setLineSpacing(1.5);
				list2.setPosition(539, 335);
				list2.setString("1. 210152\n2. 210109\n3. 210136");

				main_menu_divider_horizontal_3.setSize(sf::Vector2f(335, 1));
				main_menu_divider_horizontal_3.setOutlineThickness(2);
				back_text.setString("b. Back");
				break;

			case 6:
				header3.setString("Info: Student Account");
				instruction.setString("Guidlines: Refer to the following rules regarding proper use of student account.");

				header4_1.setPosition(157, 294);
				header4_1.setString("Student Username");
				header4_2.setPosition(533, 294);
				header4_2.setString("Contact Us");

				list1.setLineSpacing(1.25);
				list1.setPosition(73, 335);
				list1.setString("The username is provided by the school\nand it cannot be modified for being fixed.\nIt consists of the surname and last 3 digits\nin student's number, all are written in lowercase,\ne.g. Abad, Dean Harold and 210013 becomes\n'abad013.'");
				list2.setLineSpacing(1.5);
				list2.setPosition(517, 335);
				list2.setString("1. 0999-999-999\n2. help@aics.edu.ph");

				main_menu_divider_horizontal_3.setSize(sf::Vector2f(335, 1));
				main_menu_divider_horizontal_3.setOutlineThickness(2);
				back_text.setString("b. Back");
				break;

			case 7:
				header3.setString("Account Confirmation: Password");
				instruction.setString("Kindly input your student account's password for confirmation.");

				id_photo_texture_path = "content\\images\\id_photo\\sprite (0).png";
				id_photo.setTextureRect(sf::Rect(0, 0, 16, 24));
				id_photo_texture.loadFromFile(id_photo_texture_path);
				id_photo.setTexture(&id_photo_texture);

				main_menu_divider_horizontal_3.setSize(sf::Vector2f(335, 1));
				main_menu_divider_horizontal_3.setOutlineThickness(2);
				back_text.setString("b. Back");
				break;

			case 8:
				header3.setString("Student Account: Dashboard");
				instruction.setString("This is the personal information of the student AICS for academic year of 2021-2022.");
				header4_1.setPosition(195, 294);
				header4_1.setString("Account");
				header4_2.setPosition(537, 294);
				header4_2.setString("ID Photo");

				list1.setLineSpacing(1.25);
				list1.setPosition(115, 335);
				list1.setString("Name: " + name + "\nID: " + id + "\nUsername: " + username + "\nPassword: " + password + "\nTotal Grade: " + grade_string + "\nCompletion: " + completion);
				list2.setLineSpacing(1.5);
				list2.setPosition(517, 335);
				list2.setString("");

				main_menu_divider_horizontal_3.setSize(sf::Vector2f(335, 1));
				main_menu_divider_horizontal_3.setOutlineThickness(2);
				back_text.setString("b. Back");
				break;

			default:
				break;
		}

		if (grade <= 74)
		{
			completion = "Failed";
		}
		else
		{
			completion = "Passed";
		}

		sf::Time interval = sf::seconds(1.0);
		choice_cursor_blink = clock.getElapsedTime();
		//std::cout << choice_cursor_blink.asSeconds() << std::endl;
		//std::cout << interval.asSeconds() << std::endl;

		if (choice_field_highlighted == true)
		{
			if (choice_cursor_blink.asSeconds() > interval.asSeconds()) // If more than 1 second, restart the clock and count again the interval 0s-1s
			{
				clock.restart();
			}
			else if (choice_cursor_blink.asSeconds() <= interval.asSeconds() / 2) // If half of 1s i.e. 0.5s, show
			{
				choice_cursor_text_shown = true;
			}
			else // Otherwise, hide
			{
				choice_cursor_text_shown = false;
			}

			if (choice_cursor_text_shown == true) // Set the strings when shown or hidden
			{
				choice_cursor_text.setString("|");
			}
			else
			{
				choice_cursor_text.setString("");
			}
		}
		else // Text cursor is hidden when not focused on text field
		{
			choice_cursor_text.setString("");
		}

		// Update the color and text while window is open AND there is a text or none
		// This does not rely on input; it is able to update right away as soon as string is empty
		if (choice.getSize() == 0)
		{
			choice_text.setString("Choice");
			choice_text.setFillColor(sf::Color(150, 150, 150, 255)); // Gray as 'being empty'
		}
		else
		{
			choice_text.setFillColor(sf::Color(13, 71, 161, 255));
		}

		// Always draw the position of text cursor when visible
		// Find the character position by the latest size of the string of the text
		sf::Vector2f choice_cursor_position;
		choice_cursor_position = choice_text.findCharacterPos(choice.getSize());
		choice_cursor_text.setPosition(choice_cursor_position.x, 232);

		// Check all triggered events since previous iteration of loop
		while (main_window.pollEvent(an_event)) // Previous event since last iteration
		{
			switch (an_event.type)
			{
				case sf::Event::Closed:
					main_window.close(); // "close requested" event close window
					break;

				case sf::Event::MouseMoved:
					mouse_position_current = sf::Vector2f(sf::Mouse::getPosition(main_window));

					if (an_event.type == sf::Event::TextEntered)
					{
						if (choice_field_highlighted == true)
						{
							choice_field.setOutlineColor(sf::Color(13, 71, 161, 255)); // Blue
						}
						else
						{
							choice_field.setOutlineColor(sf::Color(150, 150, 150, 255)); // Gray
						}
					}
					else
					{
						if (choice_field.getGlobalBounds().contains(main_window.mapPixelToCoords(sf::Mouse::getPosition(main_window))))
						{
							choice_field.setOutlineColor(sf::Color(13, 71, 161, 255)); // Blue
						}
						else
						{
							if (choice_field_highlighted == true)
							{
								choice_field.setOutlineColor(sf::Color(13, 71, 161, 255)); // Blue
							}
							else
							{
								choice_field.setOutlineColor(sf::Color(150, 150, 150, 255)); // Gray
							}
						}

						if (choice_enter_button.getGlobalBounds().contains(main_window.mapPixelToCoords(sf::Mouse::getPosition(main_window))))
						{
							choice_enter_button.setOutlineColor(sf::Color(13, 71, 161, 255));
						}
						else
						{
							choice_enter_button.setOutlineColor(sf::Color(150, 150, 150, 255));
						}
					}

					break;

				// First, detect the mouse when inside globalBoundary of the RectangleShape
				// Then if true, proceed on highlighting the Rectangle
				// Only print necessary characters (exclude other unicode)
				// For manipulating the 'text field'
				case sf::Event::MouseButtonPressed:
					mouse_position_current = sf::Vector2f(sf::Mouse::getPosition(main_window));
					if (choice_field.getGlobalBounds().contains(main_window.mapPixelToCoords(sf::Mouse::getPosition(main_window))))
					{
						choice_field_highlighted = true;
						choice_field.setOutlineColor(sf::Color(13, 71, 161, 255)); // Blue
						choice_field.setOutlineThickness(4);
					}
					else
					{
						choice_field_highlighted = false;
					}

					if (choice_enter_button.getGlobalBounds().contains(main_window.mapPixelToCoords(sf::Mouse::getPosition(main_window))))
					{
						choice_enter_button.setOutlineColor(sf::Color(13, 71, 161, 255)); // Blue
						choice_enter_button.setOutlineThickness(4);
						choice_enter_button_text.setStyle(sf::Text::Bold);
						choice_enter_button_text.setPosition(693, 235);

						std::cout << "Current menu number: " << current_menu << std::endl;
						// Check first if string is not empty
						// Apply the same following to the mousepressed event with Enter button
						if (choice.getSize() >= 1)
						{
							// Check first if is in main menu
							switch (current_menu)
							{
								case 0:
									id_photo_num = 0;

									if (choice == "1" || choice == "BS1MA" || choice == "Bs1ma" || choice == "bs1ma")
									{
										current_menu = 1;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "2" || choice == "BS2MA" || choice == "Bs2ma" || choice == "bs2ma")
									{
										current_menu = 2;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "3" || choice == "BS3MA" || choice == "Bs3ma" || choice == "bs3ma")
									{
										current_menu = 3;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "4" || choice == "BS4MA" || choice == "Bs4ma" || choice == "bs4ma")
									{
										current_menu = 4;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "5" || choice == "BS5MA" || choice == "Bs5ma" || choice == "bs5ma")
									{
										current_menu = 5;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "i" || choice == "I" || choice == "INFO" || choice == "Info" || choice == "info")
									{
										current_menu = 6;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								// In section BS1MA
								case 1:
									id_photo_num = 0;

									if (choice == "1" || choice == "Albao, Melvin James" || choice == "Melvin James Albao" || choice == "albao781" || choice == "170781")
									{
										current_menu = 7;
										last_menu = 1;

										name = "Melvin James Albao";
										username = "albao781";
										id = "170781";
										grade = 97;
										grade_string = std::to_string(grade);

										id_photo_num = 1;

										choice = "";
									}
									else if (choice == "2" || choice == "Consejero, Viviane" || choice == "Viviane Consejero" || choice == "consejero715" || choice == "180715")
									{
										current_menu = 7;
										last_menu = 1;

										name = "Viviane Consejero";
										username = "consejero715";
										id = "180715";
										grade = 97;
										grade_string = std::to_string(grade);

										id_photo_num = 2;

										choice = "";
									}
									else if (choice == "3" || choice == "Tomas, Aljean Santos" || choice == "Aljean Santos Tomas" || choice == "tomas226" || choice == "141226")
									{
										current_menu = 7;
										last_menu = 1;

										name = "Aljean Santos Tomas";
										username = "tomas226";
										id = "141226";
										grade = 97;
										grade_string = std::to_string(grade);

										id_photo_num = 3;

										choice = "";
									}
									else if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = 0;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								// In section BS2MA
								case 2:
									id_photo_num = 0;

									if (choice == "1" || choice == "Abad, Dean Harold" || choice == "Dean Harold Abad" || choice == "abad013" || choice == "210013")
									{
										current_menu = 7;
										last_menu = 2;

										name = "Dean Harold Abad";
										username = "abad013";
										id = "210013";
										grade = 97;

										id_photo_num = 4;

										choice = "";
									}
									else if (choice == "2" || choice == "Domodon, Althea" || choice == "Althea Domodon" || choice == "domodon365" || choice == "190365")
									{
										current_menu = 7;
										last_menu = 2;

										name = "Althea Domodon";
										username = "domodon365";
										id = "190365";
										grade = 97;

										id_photo_num = 5;

										choice = "";
									}
									else if (choice == "3" || choice == "Fortes, Jhon Emerson" || choice == "Jhon Emerson Fortes" || choice == "fortes001" || choice == "210001")
									{
										current_menu = 7;
										last_menu = 2;

										name = "Jhon Emerson Fortes";
										username = "fortes001";
										id = "210001";
										grade = 97;

										id_photo_num = 6;

										choice = "";
									}
									else if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = 0;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								// In section BS3MA
								case 3:
									id_photo_num = 0;

									if (choice == "1" || choice == "Baclaan, Rocel" || choice == "Rocel Baclaan" || choice == "baclaan041" || choice == "210041")
									{
										current_menu = 7;
										last_menu = 3;

										name = "Rocel Baclaan";
										username = "baclaan041";
										id = "210041";
										grade = 97;

										id_photo_num = 7;

										choice = "";
									}
									else if (choice == "2" || choice == "Fabella, Joshua" || choice == "Joshua Fabella" || choice == "fabella076" || choice == "210076")
									{
										current_menu = 7;
										last_menu = 3;

										name = "Joshua Fabella";
										username = "fabella076";
										id = "210076";
										grade = 97;

										id_photo_num = 8;

										choice = "";
									}
									else if (choice == "3" || choice == "Pulmano, Johnmark" || choice == "Johnmark Pulmano" || choice == "pulmano057" || choice == "210057")
									{
										current_menu = 7;
										last_menu = 3;

										name = "Johnmark Pulmano";
										username = "pulmano057";
										id = "210057";
										grade = 97;

										id_photo_num = 9;

										choice = "";
									}
									else if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = 0;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								// In section BS4MA
								case 4:
									id_photo_num = 0;

									if (choice == "1" || choice == "Castillo, Dawn Xyly" || choice == "Dawn Xyly Castillo" || choice == "castillo089" || choice == "210089")
									{
										current_menu = 7;
										last_menu = 4;

										name = "Dawn Xyly Castillo";
										username = "castillo089";
										id = "210089";
										grade = 98;

										id_photo_num = 10;

										choice = "";
									}
									else if (choice == "2" || choice == "Nepacena, John Jomar" || choice == "John Jomar Nepacena" || choice == "nepacena077" || choice == "210077")
									{
										current_menu = 7;
										last_menu = 4;

										name = "John Jomar Nepacena";
										username = "nepacena077";
										id = "210077";
										grade = 98;

										id_photo_num = 11;

										choice = "";
									}
									else if (choice == "3" || choice == "Villafuerte, Sean" || choice == "Sean Villafuerte" || choice == "villafuerte101" || choice == "210101")
									{
										current_menu = 7;
										last_menu = 4;

										name = "Sean Villafuerte";
										username = "villafuerte101";
										id = "210101";
										grade = 98;

										id_photo_num = 12;

										choice = "";
									}
									else if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = 0;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								// In section BS5MA
								case 5:
									id_photo_num = 0;

									if (choice == "1" || choice == "Bonavente, Timothy" || choice == "Timothy Bonavente" || choice == "bonavente152" || choice == "210152")
									{
										current_menu = 7;
										last_menu = 5;

										name = "Timothy Bonavente";
										username = "bonavente152";
										id = "210152";
										grade = 98;

										id_photo_num = 13;

										choice = "";
									}
									else if (choice == "2" || choice == "Latoja, Jiggs Venick" || choice == "Jiggs Venick Latoja" || choice == "latoja109" || choice == "210109")
									{
										current_menu = 7;
										last_menu = 5;

										name = "Jiggs Venick Latoja";
										username = "latoja109";
										id = "210109";
										grade = 97;

										id_photo_num = 14;

										choice = "";
									}
									else if (choice == "3" || choice == "Pasildo, Edmund Paul" || choice == "Edmund Paul Pasildo" || choice == "pasildo136" || choice == "210136")
									{
										current_menu = 7;
										last_menu = 5;

										name = "Edmund Paul Pasildo";
										username = "pasildo136";
										id = "210136";
										grade = 98;

										id_photo_num = 15;

										choice = "";
									}
									else if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = 0;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								case 6:
									id_photo_num = 0;

									if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = 0;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								case 7:
									if (choice.getSize() >= 8)
									{
										password = choice;
										current_menu = 8;
										last_menu = last_menu;
										choice = "";
									}
									else if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = last_menu;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								case 8:
									if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = last_menu;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								default:
									break;
							}
						}
						else
						{
							// Prompt to try again
							std::cout << "Invalid input. Please try again.\n";
							choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
							choice_field.setOutlineThickness(4);
						}
					}
					else
					{
						choice_enter_button.setOutlineColor(sf::Color(150, 150, 150, 255)); // Gray
						choice_enter_button.setOutlineThickness(2);
					}
					break;

				case sf::Event::TextEntered:
					if (choice_field_highlighted == true)
					{
						if (
							// Check for number characters
							((an_event.text.unicode >= 48) && (an_event.text.unicode <= 57)) ||
							// Check for capital letters
							((an_event.text.unicode >= 65) && (an_event.text.unicode <= 90)) ||
							// Check for lowercase letters
							((an_event.text.unicode >= 97) && (an_event.text.unicode <= 122)) ||
							// Check for space and other special characters from SPACE to /
							((an_event.text.unicode >= 32) && (an_event.text.unicode <= 47)) ||
							// Check for special characters from : to @
							((an_event.text.unicode >= 58) && (an_event.text.unicode <= 64)) ||
							// Check for special characters from [ to `
							((an_event.text.unicode >= 91) && (an_event.text.unicode <= 96)) ||
							// Check for special characters from { to ~
							((an_event.text.unicode >= 123) && (an_event.text.unicode <= 126)))
						{
							// Check if character size of the string is under or 28 in total counts
							if (choice.getSize() <= 28)
							{
								choice += an_event.text.unicode;
								choice_text.setString(choice);
							}
						}
						// If unicode refers to backspace
						else if (an_event.text.unicode == 8)
						{
							// Do not erase unless string size is not 0
							if (choice.getSize() >= 1)
							{
								choice.erase(choice.getSize() - 1, 1); // InitPos @ N-1
								choice_text.setString(choice);
							}
						}
						// If unicode refers to delete - CHANGE THIS LATER IN CORRESPONDING TO CHARACTER'S POSITION
						else if (an_event.text.unicode == 127)
						{
							// Do not erase unless string size is not 0
							if (choice.getSize() >= 1)
							{
								choice.erase(choice.getSize() - 1, 1); // InitPos @ focus position
								choice_text.setString(choice);
							}
						}
					}
					break;

				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						std::cout << "Current menu number: " << current_menu << std::endl;
						// Check first if string is not empty
						// Apply the same following to the mousepressed event with Enter button
						if (choice.getSize() >= 1)
						{
							// Check first if is in main menu
							switch (current_menu)
							{
								case 0:
									id_photo_num = 0;

									if (choice == "1" || choice == "BS1MA" || choice == "Bs1ma" || choice == "bs1ma")
									{
										current_menu = 1;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "2" || choice == "BS2MA" || choice == "Bs2ma" || choice == "bs2ma")
									{
										current_menu = 2;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "3" || choice == "BS3MA" || choice == "Bs3ma" || choice == "bs3ma")
									{
										current_menu = 3;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "4" || choice == "BS4MA" || choice == "Bs4ma" || choice == "bs4ma")
									{
										current_menu = 4;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "5" || choice == "BS5MA" || choice == "Bs5ma" || choice == "bs5ma")
									{
										current_menu = 5;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "i" || choice == "I" || choice == "INFO" || choice == "Info" || choice == "info")
									{
										current_menu = 6;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								// In section BS1MA
								case 1:
									id_photo_num = 0;

									if (choice == "1" || choice == "Albao, Melvin James" || choice == "Melvin James Albao" || choice == "albao781" || choice == "170781")
									{
										current_menu = 7;
										last_menu = 1;

										name = "Melvin James Albao";
										username = "albao781";
										id = "170781";
										grade = 97;
										grade_string = std::to_string(grade);

										id_photo_num = 1;

										choice = "";
									}
									else if (choice == "2" || choice == "Consejero, Viviane" || choice == "Viviane Consejero" || choice == "consejero715" || choice == "180715")
									{
										current_menu = 7;
										last_menu = 1;

										name = "Viviane Consejero";
										username = "consejero715";
										id = "180715";
										grade = 97;
										grade_string = std::to_string(grade);

										id_photo_num = 2;

										choice = "";
									}
									else if (choice == "3" || choice == "Tomas, Aljean Santos" || choice == "Aljean Santos Tomas" || choice == "tomas226" || choice == "141226")
									{
										current_menu = 7;
										last_menu = 1;

										name = "Aljean Santos Tomas";
										username = "tomas226";
										id = "141226";
										grade = 97;
										grade_string = std::to_string(grade);

										id_photo_num = 3;

										choice = "";
									}
									else if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = 0;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								// In section BS2MA
								case 2:
									id_photo_num = 0;

									if (choice == "1" || choice == "Abad, Dean Harold" || choice == "Dean Harold Abad" || choice == "abad013" || choice == "210013")
									{
										current_menu = 7;
										last_menu = 2;

										name = "Dean Harold Abad";
										username = "abad013";
										id = "210013";
										grade = 97;

										id_photo_num = 4;

										choice = "";
									}
									else if (choice == "2" || choice == "Domodon, Althea" || choice == "Althea Domodon" || choice == "domodon365" || choice == "190365")
									{
										current_menu = 7;
										last_menu = 2;

										name = "Althea Domodon";
										username = "domodon365";
										id = "190365";
										grade = 97;

										id_photo_num = 5;

										choice = "";
									}
									else if (choice == "3" || choice == "Fortes, Jhon Emerson" || choice == "Jhon Emerson Fortes" || choice == "fortes001" || choice == "210001")
									{
										current_menu = 7;
										last_menu = 2;

										name = "Jhon Emerson Fortes";
										username = "fortes001";
										id = "210001";
										grade = 97;

										id_photo_num = 6;

										choice = "";
									}
									else if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = 0;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								// In section BS3MA
								case 3:
									id_photo_num = 0;

									if (choice == "1" || choice == "Baclaan, Rocel" || choice == "Rocel Baclaan" || choice == "baclaan041" || choice == "210041")
									{
										current_menu = 7;
										last_menu = 3;

										name = "Rocel Baclaan";
										username = "baclaan041";
										id = "210041";
										grade = 97;

										id_photo_num = 7;

										choice = "";
									}
									else if (choice == "2" || choice == "Fabella, Joshua" || choice == "Joshua Fabella" || choice == "fabella076" || choice == "210076")
									{
										current_menu = 7;
										last_menu = 3;

										name = "Joshua Fabella";
										username = "fabella076";
										id = "210076";
										grade = 97;

										id_photo_num = 8;

										choice = "";
									}
									else if (choice == "3" || choice == "Pulmano, Johnmark" || choice == "Johnmark Pulmano" || choice == "pulmano057" || choice == "210057")
									{
										current_menu = 7;
										last_menu = 3;

										name = "Johnmark Pulmano";
										username = "pulmano057";
										id = "210057";
										grade = 97;

										id_photo_num = 9;

										choice = "";
									}
									else if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = 0;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								// In section BS4MA
								case 4:
									id_photo_num = 0;

									if (choice == "1" || choice == "Castillo, Dawn Xyly" || choice == "Dawn Xyly Castillo" || choice == "castillo089" || choice == "210089")
									{
										current_menu = 7;
										last_menu = 4;

										name = "Dawn Xyly Castillo";
										username = "castillo089";
										id = "210089";
										grade = 98;

										id_photo_num = 10;

										choice = "";
									}
									else if (choice == "2" || choice == "Nepacena, John Jomar" || choice == "John Jomar Nepacena" || choice == "nepacena077" || choice == "210077")
									{
										current_menu = 7;
										last_menu = 4;

										name = "John Jomar Nepacena";
										username = "nepacena077";
										id = "210077";
										grade = 98;

										id_photo_num = 11;

										choice = "";
									}
									else if (choice == "3" || choice == "Villafuerte, Sean" || choice == "Sean Villafuerte" || choice == "villafuerte101" || choice == "210101")
									{
										current_menu = 7;
										last_menu = 4;

										name = "Sean Villafuerte";
										username = "villafuerte101";
										id = "210101";
										grade = 98;

										id_photo_num = 12;

										choice = "";
									}
									else if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = 0;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								// In section BS5MA
								case 5:
									id_photo_num = 0;

									if (choice == "1" || choice == "Bonavente, Timothy" || choice == "Timothy Bonavente" || choice == "bonavente152" || choice == "210152")
									{
										current_menu = 7;
										last_menu = 5;

										name = "Timothy Bonavente";
										username = "bonavente152";
										id = "210152";
										grade = 98;

										id_photo_num = 13;

										choice = "";
									}
									else if (choice == "2" || choice == "Latoja, Jiggs Venick" || choice == "Jiggs Venick Latoja" || choice == "latoja109" || choice == "210109")
									{
										current_menu = 7;
										last_menu = 5;

										name = "Jiggs Venick Latoja";
										username = "latoja109";
										id = "210109";
										grade = 97;

										id_photo_num = 14;

										choice = "";
									}
									else if (choice == "3" || choice == "Pasildo, Edmund Paul" || choice == "Edmund Paul Pasildo" || choice == "pasildo136" || choice == "210136")
									{
										current_menu = 7;
										last_menu = 5;

										name = "Edmund Paul Pasildo";
										username = "pasildo136";
										id = "210136";
										grade = 98;

										id_photo_num = 15;

										choice = "";
									}
									else if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = 0;
										last_menu = 0;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								case 6:
									id_photo_num = 0;

									if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = 0;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								case 7:
									if (choice.getSize() >= 8)
									{
										password = choice;
										current_menu = 8;
										last_menu = last_menu;
										choice = "";
									}
									else if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = last_menu;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								case 8:
									if (choice == "b" || choice == "B" || choice == "BACK" || choice == "Back" || choice == "back")
									{
										id_photo_num = 0;
										current_menu = last_menu;
										choice = "";
									}
									else if (choice == "q" || choice == "Q" || choice == "QUIT" || choice == "Quit" || choice == "quit")
									{
										exit(1);
									}
									else
									{
										// Prompt to try again
										std::cout << "Invalid input. Please try again.\n";
										choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
										choice_field.setOutlineThickness(4);
									}
									break;

								default:
									break;
							}
						}
						else
						{
							// Prompt to try again
							std::cout << "Invalid input. Please try again.\n";
							choice_field.setOutlineColor(sf::Color(204, 0, 0, 255)); // Red
							choice_field.setOutlineThickness(4);
						}
					}
					break;

				default:
					if (choice_field.getGlobalBounds().contains(main_window.mapPixelToCoords(sf::Mouse::getPosition(main_window))))
					{
						if (choice_field_highlighted == true)
						{
							choice_field.setOutlineColor(sf::Color(13, 71, 161, 255)); // Blue
							choice_field.setOutlineThickness(2);
						}
						else
						{
							choice_field.setOutlineColor(sf::Color(150, 150, 150, 255)); // Gray
							choice_field.setOutlineThickness(2);
						}
					}
					else
					{
						if (choice_field_highlighted == true)
						{
							choice_field.setOutlineColor(sf::Color(13, 71, 161, 255)); // Blue
							choice_field.setOutlineThickness(2);
						}
						else
						{
							choice_field.setOutlineColor(sf::Color(150, 150, 150, 255)); // Gray
							choice_field.setOutlineThickness(2);
						}
					}

					if (choice_enter_button.getGlobalBounds().contains(main_window.mapPixelToCoords(sf::Mouse::getPosition(main_window))))
					{
						choice_enter_button.setOutlineColor(sf::Color(13, 71, 161, 255)); // Blue
						choice_enter_button.setOutlineThickness(2);
						choice_enter_button_text.setStyle(sf::Text::Regular);
						choice_enter_button_text.setPosition(695, 235);
					}
					else
					{
						choice_enter_button.setOutlineColor(sf::Color(150, 150, 150, 255)); // Gray
						choice_enter_button.setOutlineThickness(2);
						choice_enter_button_text.setStyle(sf::Text::Regular);
						choice_enter_button_text.setPosition(695, 235);
					}
					break;
			}
		}

		main_window.clear(sf::Color(sf::Color::White)); // Clear screen w/ color 'flash' arg
		// Nevermind, just change the values of the texts when navigating between menus
		// Drawing START - rear
		main_window.draw(wallpaper);
		main_window.draw(background_board);
		main_window.draw(header1); // School name and years
		main_window.draw(header2); // Application context
		main_window.draw(header3); // Displayed menu's name
		main_window.draw(logo_circle);
		main_window.draw(pseudoline1);
		main_window.draw(pseudoline2);
		main_window.draw(mini_board);
		main_window.draw(instruction);
		main_window.draw(choice_field);
		main_window.draw(choice_enter_button);
		main_window.draw(choice_text);
		main_window.draw(choice_cursor_text);
		main_window.draw(choice_enter_button_text);
		main_window.draw(main_menu_list);
		main_window.draw(main_menu_divider_vertical);
		main_window.draw(main_menu_divider_horizontal_1);
		main_window.draw(main_menu_divider_horizontal_2);
		// Back Option START
		main_window.draw(main_menu_divider_horizontal_3);
		main_window.draw(back_text);
		// Back Option END
		// Student Account ID Photo START
		main_window.draw(id_photo);
		// Student Account ID Photo START
		main_window.draw(header4_1);
		main_window.draw(header4_2);
		main_window.draw(list1);
		main_window.draw(list2);
		main_window.draw(credits);
		// Drawing END - front
		main_window.display(); // Update the window
	}

	return 0;
}