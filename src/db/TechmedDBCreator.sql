BEGIN TRANSACTION;
CREATE TABLE User_Tag(id_user_tag INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER NOT NULL, tag_id INTEGER NOT NULL,FOREIGN KEY(user_id) REFERENCES User(id_user),FOREIGN KEY(tag_id) REFERENCES Tag(id_tag));
CREATE TABLE "User" (
	`id_user`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`user_lastname`	TEXT NOT NULL,
	`user_firstname`	TEXT NOT NULL,
	`user_group`	INTEGER NOT NULL,
	`user_right`	INTEGER NOT NULL,
	`user_description`	TEXT,
	`user_passeword`	TEXT NOT NULL,
	FOREIGN KEY(`user_group`) REFERENCES `Tag`(`id_tag`),
	FOREIGN KEY(`user_right`) REFERENCES `Tag`(`id_tag`)
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
INSERT INTO `Type` VALUES (5,'user right','define the user''s right type');
INSERT INTO `Type` VALUES (6,'user group','define the group of the user');
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
INSERT INTO `Tag` VALUES (12,'US',2,NULL);
INSERT INTO `Tag` VALUES (13,'guest',5,NULL);
INSERT INTO `Tag` VALUES (14,'user',5,NULL);
INSERT INTO `Tag` VALUES (15,'admin',5,NULL);
INSERT INTO `Tag` VALUES (16,'Dr.',6,NULL);
INSERT INTO `Tag` VALUES (17,'Pr.',6,NULL);
INSERT INTO `Tag` VALUES (18,'administrateur',6,NULL);
INSERT INTO `Tag` VALUES (19,'patient',6,NULL);
INSERT INTO `Tag` VALUES (20,'secrétaire',6,NULL);
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
