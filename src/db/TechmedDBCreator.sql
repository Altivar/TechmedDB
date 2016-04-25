BEGIN TRANSACTION;
CREATE TABLE "User_Group" (
	`id_group`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`group_name`	TEXT NOT NULL,
	`group_description`	TEXT,
	`group_right`	INTEGER NOT NULL
);
INSERT INTO `User_Group` VALUES (1,'read_only',NULL,0);
INSERT INTO `User_Group` VALUES (2,'read_add',NULL,0);
INSERT INTO `User_Group` VALUES (3,'read_modify_add',NULL,0);
INSERT INTO `User_Group` VALUES (4,'administrator',NULL,0);
CREATE TABLE `User` (
	`id_user`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`user_name`	TEXT NOT NULL,
	`user_group`	INTEGER NOT NULL,
	FOREIGN KEY(`user_group`) REFERENCES User_Group('id_group')
);
CREATE TABLE `Type` (
	`id_type`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`type_name`	TEXT NOT NULL,
	`type_description`	TEXT
);
INSERT INTO `Type` VALUES (1,'tag','tag');
INSERT INTO `Type` VALUES (2,'modality','modality of acquirement');
INSERT INTO `Type` VALUES (3,'pathology','pathology of patient');
INSERT INTO `Type` VALUES (4,'region','anatommical region');
CREATE TABLE `Tag` (
	`id_tag`	INTEGER NOT NULL,
	`tag_name`	TEXT NOT NULL,
	`tag_type`	INTEGER NOT NULL,
	`tag_reference`	INTEGER,
	PRIMARY KEY(id_tag),
	FOREIGN KEY(`tag_type`) REFERENCES Type('id_type'),
	FOREIGN KEY(`tag_reference`) REFERENCES Tag('id_tag')
);
INSERT INTO `Tag` VALUES (1,'MRI',2,NULL);
INSERT INTO `Tag` VALUES (2,'IRM',2,1);
INSERT INTO `Tag` VALUES (3,'MR',2,1);
INSERT INTO `Tag` VALUES (4,'Scanner',2,NULL);
INSERT INTO `Tag` VALUES (5,'Radiography',2,NULL);
INSERT INTO `Tag` VALUES (6,'X-Ray',2,5);
INSERT INTO `Tag` VALUES (7,'X Ray',2,5);
INSERT INTO `Tag` VALUES (8,'XRay',2,5);
INSERT INTO `Tag` VALUES (9,'Radio',2,5);
INSERT INTO `Tag` VALUES (10,'Radiographie',2,5);
INSERT INTO `Tag` VALUES (11,'Rayons X',2,5);
INSERT INTO `Tag` VALUES (12,'US',0,NULL);
INSERT INTO `Tag` VALUES (13,'',0,NULL);
INSERT INTO `Tag` VALUES (14,'',0,NULL);
INSERT INTO `Tag` VALUES (15,'',0,NULL);
INSERT INTO `Tag` VALUES (16,'',0,NULL);
CREATE TABLE `File_Tag` (
	`id_file_tag`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`id_tag`	INTEGER NOT NULL,
	`id_file`	INTEGER NOT NULL,
	FOREIGN KEY(`id_tag`) REFERENCES Tag('id_tag'),
	FOREIGN KEY(`id_file`) REFERENCES File('id_file')
);
CREATE TABLE `File` (
	`id_file`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`file_url`	TEXT NOT NULL,
	`file_source`	INTEGER,
	`file_author`	INTEGER NOT NULL,
	`file_patient`	INTEGER NOT NULL,
	`file_creation_date`	TEXT NOT NULL,
	`file_last_modification_date`	TEXT NOT NULL,
	`file_md5sum`	TEXT NOT NULL,
	FOREIGN KEY(`file_source`) REFERENCES File('id_file'),
	FOREIGN KEY(`file_author`) REFERENCES User('id_user'),
	FOREIGN KEY(`file_patient`) REFERENCES User('id_user')
);
COMMIT;
