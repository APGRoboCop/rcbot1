# rcbot1
RCbot created by Cheeseh | This is a enhancement build for Sven Co-op v5.x

http://rcbot.bots-united.com/

1. Install & Supported Mods
2. Playing
3. Commands
4. Waypoints
5. Admin Use
6. Faq
7. Reporting bugs
8. Credits

=--------=
1. Install
=--------=

First of all EXTRACT all files into the Half-Life Folder, it should create a
folder called rcbot inside HL folder with all the files in it.

REMEMBER : Extract it to Half-Life folder ONLY, NOT the MOD folder i.e.
bot files must be in Half-Life/rcbot

For LINUX see the linux_install.txt file for details.

---------
Windows : 
---------
WITHOUT METAMOD:

Make sure you have downloaded the NON-metamod version for WINDOWS.

Extract the zip into the Half-life folder, make sure all files are
in the Half-Life folder/rcbot directory.

Open the liblist.gam file (in the MOD folder that you want to play)...
with a suitable text editing program and then EDIT the line (do not 
make a copy of the line or else the bot won't work!):

gamedll "<MOD_DLL>"

to 

gamedll "../rcbot/dlls/rcbot.dll"

--------------------------------------------------------------
WITH METAMOD:

Make sure you have downloaded the METAMOD version of the bot for WINDOWS.

Extract the zip into the Half-life folder, make sure all files are
in the Half-Life folder/rcbot directory.

Go into addons/metamod directory and EDIT the plugins.ini file

Add the line:

win32 ../rcbot/dlls/rcbot_mm.dll

to the file.

--------------
Supported Mods
--------------

Natural Selection 2.01/3.0
Svencoop
Deathmatch Classic 
HL Bumpercars 1.5 [and above]
Rocket crowbar 2
HL deathmatch

=--------=
2. Playing
=--------=

Once you've created  a game, and you want to add bots, use the  console command
"rcbot addbot"

-OR- bind a key to "rcbot bot_menu"

and Select "Add Random Bot" To add a bot.

If playing NS you can use the bot menu to tell which team you want the new bot
to join. Select the "Add bot to team" menu item and select the team you want.

You can also kick bots from the game by using the bot menu (bot_menu command).

You can set up min_bots and max_bots setting in the config file.
Read the rcbot_commands.txt about these commands.

=--------=
3. Commands
=--------=

The commands are slightly different from last versions but most commands are the same
but to access them you must type "rcbot" before each, incase other bots are running
and have the same commands.

Read the rcbot_commands.txt file about the commands.

=--------=
4. Waypoints
=--------=

The waypoints are slightly different from last versions but most commands are the same
but to access them you must type "rcbot" before each, incase other bots are running
and have the same commands.

Read the rcbot_commands.txt file about the commands or rcbot_waypoint_readme.txt

=--------=
5. Admin Use
=--------=

If you want to have access to bot commands on a dedicated server or another server
you must set up your name and password on the bot_users.ini file on the server.

Open and read the bot_users.ini file for details on how to make a user.

Then whilst in the game your name must be that same name as written in the config file,
and type the command

rcbot set_pass <your password in bot_users.ini file>

this will authenticate you and if successful you should have access to the bot commands
with the access level written in the bot_users.ini next to your name & password.

=--------=
6. Faq
=--------=

SEE faq.htm that comes with the bot! It will be in the rcbot folder.

!!!Also, check out the FAQ page on the rcbot site www.rcbot.net for the latest FAQ page!!!

=-------------------=
7. Reporting Bugs
=-------------------=

Please follow these steps.

i.   Make sure the bug hasn't been mentioned as a known problem
ii.  Check the rcbot forum (http://rcbot.bots-united.com/forums) for current bug reports made
iii. Post in forum or e-mail me with :

     What map you were playing,
     What you think the bot(s) are trying to do,
     Info in your config file.

=--------------=
8. Credits
=--------------=

Botman : for the main HPB_Bot template
Flayra : for NS and code needed to get a bot to work with NS
Sven Viking : for SvenCoop and allowing me access to Beta versions to allow bot support  
PM (@RACC-ai.com) : for good FakeClientCommand code.
SandMan : For waypointing NS maps