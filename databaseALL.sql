BEGIN TRANSACTION;
CREATE TABLE Enemy (id_weapon NUMERIC, id_enemy INTEGER PRIMARY KEY, name TEXT, damage NUMERIC, shield NUMERIC, experience NUMERIC);
INSERT INTO Enemy VALUES(1,1,'Butterfly',30,20,20);
INSERT INTO Enemy VALUES(1,2,'Troll',30,30,30);
INSERT INTO Enemy VALUES(2,3,'Wolf',35,30,35);
INSERT INTO Enemy VALUES(4,4,'Orc',40,40,50);
INSERT INTO Enemy VALUES(2,5,'Lizard',45,45,55);
INSERT INTO Enemy VALUES(3,6,'Snake',50,50,60);
INSERT INTO Enemy VALUES(4,7,'Mage',50,50,65);
INSERT INTO Enemy VALUES(5,8,'DarkElf',50,55,70);
INSERT INTO Enemy VALUES(6,9,'Vampire',55,55,75);
INSERT INTO Enemy VALUES(7,10,'Palladin',60,55,80);
INSERT INTO Enemy VALUES(8,11,'Manticore',65,50,90);
INSERT INTO Enemy VALUES(8,12,'Basilisk',70,50,100);
INSERT INTO Enemy VALUES(9,13,'Sphinx',80,60,120);
INSERT INTO Enemy VALUES(5,14,'Slaad',90,60,130);
INSERT INTO Enemy VALUES(10,15,'Balor',100,100,600);
CREATE TABLE Save (id_save INTEGER PRIMARY KEY, name TEXT, gender TEXT, class TEXT, hp NUMERIC, hp_max NUMERIC, strenght NUMERIC, armour NUMERIC, magic NUMERIC, experience NUMERIC, level NUMERIC, level_up_exp NUMERIC, xlocation NUMERIC, ylocation NUMERIC);
INSERT INTO Save VALUES(1,'Michal','Male','Mage',100,100,10,10,10,10,1,100,1,1);
INSERT INTO Save VALUES(2,'Gavaskar','Female','Archer',100,100,20,40,10,55,1,100,1,1);
CREATE TABLE Weapons (id_weapon INTEGER PRIMARY KEY, name_weapon TEXT, damage_weapon );
INSERT INTO Weapons VALUES(1,'Dagger',10);
INSERT INTO Weapons VALUES(2,'Knife',15);
INSERT INTO Weapons VALUES(3,'Sword',20);
INSERT INTO Weapons VALUES(4,'Axe',25);
INSERT INTO Weapons VALUES(5,'Battleaxe',30);
INSERT INTO Weapons VALUES(6,'Mace',35);
INSERT INTO Weapons VALUES(7,'Hammer',40);
INSERT INTO Weapons VALUES(8,'Longsword',45);
INSERT INTO Weapons VALUES(9,'Rapier',50);
INSERT INTO Weapons VALUES(10,'Blade',60);
CREATE TABLE Potions (id_Potions NUMERIC, name TEXT, health NUMERIC, damage NUMERIC, shield NUMERIC)
INSERT INTO Potions VALUES(1, 'sheild buff', 0, 0, 50 );
INSERT INTO Potions VALUES(2, 'shield BOUFFF', 0, 0, 100 );
INSERT INTO Potions VALUES(3, 'health boost', 50, 0, 0);
INSERT INTO Potions VALUES(4, 'health slurp', 100, 0, 0);
COMMIT;
