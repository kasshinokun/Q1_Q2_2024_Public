CREATE DATABASE IF NOT EXISTS db_receipt;
/*Add on future code
CHARACTER SET utf8 
COLLATE utf8_general_ci 
DEFAULT ENCRYPTION = 'Y'; #Create database

*//*
This sql template script uses Brazil data terminology
to generate entities, attributes and relationships. 
Its focus is to be a prelude to a personal project, 
but aiming to help anyone who wants to use.

hints:
citizen as pessoa_fisica
enterprise as pessoa_juridica
client as pessoa
*/
#Need review
CREATE TABLE pessoa(
	Person_Id int auto_increment primary key,
    Person_FullName varchar(255),
    Person_Sign varchar(255) unique,
    Person_Cpf_Cnpj varchar(255) unique
);
CREATE TABLE pessoa_fisica(
	P_F_Id int not null,
    P_F_Rg varchar(20) unique,
    CONSTRAINT FK_P_F_Id FOREIGN KEY (P_F_Id) REFERENCES pessoa(Person_ID)
);
CREATE TABLE pessoa_juridica(
	P_J_Id int not null,
    P_J_IMunicipal varchar(20) unique,
    P_J_IEstadual varchar(20) unique,
    CONSTRAINT FK_P_J_Id FOREIGN KEY (P_J_Id) REFERENCES pessoa(PersonID)
);
