#if necessary .....
DROP DATABASE IF EXISTS db_receipt;
#Create database
CREATE DATABASE IF NOT EXISTS db_receipt
charset utf8mb4 
collate utf8mb4_general_ci; 

/*
DEFAULT ENCRYPTION = 'Y';
*/
/*
This sql template script uses Brazil data terminology
to generate entities, attributes and relationships. 
Its focus is to be a prelude to a personal project, 
but aiming to help anyone who wants to use.

hints:
citizen as pessoa_fisica
enterprise as pessoa_juridica
client as pessoa
*/

#if necessary, and the other tables have not been created....
USE db_receipt;
DROP TABLE IF EXISTS pessoa;
#Create table 1
USE db_receipt;
CREATE TABLE IF NOT EXISTS pessoa(
	Person_Id int auto_increment,
    Person_FullName varchar(200),
    Person_Sign varchar(10),
    Person_Cpf_Cnpj varchar(20),
    PRIMARY KEY(Person_Id), #simple definition
    UNIQUE KEY(Person_Sign, Person_Cpf_Cnpj) #simple definition
);
#if necessary .....
USE db_receipt;
DROP TABLE IF EXISTS pessoa_fisica;
#Create table 2
USE db_receipt;
CREATE TABLE IF NOT EXISTS pessoa_fisica(
	P_F_Id int not null,
    P_F_Rg varchar(20),
    CONSTRAINT PK_P_F_Id primary key (P_F_Id),
    CONSTRAINT FK_P_F_Id FOREIGN KEY (P_F_Id) REFERENCES pessoa(Person_ID), #usual defintion
    CONSTRAINT UK_P_F_Rg UNIQUE KEY (P_F_Rg) #usual defintion
);
#if necessary .....
USE db_receipt;
DROP TABLE IF EXISTS pessoa_juridica;
#Create table 3
USE db_receipt;
CREATE TABLE IF NOT EXISTS pessoa_juridica(
	P_J_Id int not null,
    P_J_IMunicipal varchar(20) unique,
    P_J_IEstadual varchar(20) unique,
    FOREIGN KEY (P_J_Id) REFERENCES pessoa(Person_ID) #usual defintion
);
#above is ready to use

#if necessary .....
USE db_receipt;
DROP TABLE IF EXISTS tbl_receipt;
#Create table 4
USE db_receipt;
#on development
CREATE TABLE IF NOT EXISTS tbl_receipt(
	Receipt_ref varchar(20) not null,
    Receipt_P_id int not null,
    Receipt_date date not null,
    Receipt_cod int not null,
    Receipt_vl decimal not null,
    FOREIGN KEY (Receipt_P_id) REFERENCES pessoa(Person_id), #usual defintion
    CONSTRAINT PK_Receipt_ref PRIMARY KEY (Receipt_cod/*,month_year(Receipt_cod),get_sign(Receipt_P_id)*/), #usual defintion
    UNIQUE KEY(Receipt_ref)
    
);
#functions on development
#month_year(my_date date)
#get_sign(unknow int)
