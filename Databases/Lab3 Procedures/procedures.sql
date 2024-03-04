use [Chain of Car Dealerships]
go
CREATE TABLE CrtVersion(
version int)
CREATE TABLE StoredProcedures
(
uspUp VARCHAR(40),
uspDown VARCHAR(40),
PRIMARY KEY (uspUp,uspDown),
targetVersion TINYINT
)
GO
CREATE OR ALTER PROCEDURE uspSetSlotsToVarchar AS ALTER TABLE Garage ALTER COLUMN slots VARCHAR(5)
GO
CREATE OR ALTER PROCEDURE uspSetSlotsToInt AS ALTER TABLE Garage ALTER COLUMN slots INT

GO
CREATE OR ALTER PROCEDURE uspAddTelephoneToClient AS ALTER TABLE Client ADD Telephone varchar(10)
GO 
CREATE OR ALTER PROCEDURE uspDropTelephoneClient AS ALTER TABLE Client DROP COLUMN Telephone




GO
CREATE OR ALTER PROCEDURE uspAddConstraintGoodCredit AS ALTER TABLE Client ADD CONSTRAINT GoodCredZero DEFAULT 0 for good_credit
GO 
CREATE OR ALTER PROCEDURE uspDropConstraintGoodCredit AS ALTER TABLE Client DROP CONSTRAINT GoodCredZero



GO
CREATE OR ALTER PROCEDURE uspAddFKRepairParts AS ALTER TABLE RepairParts ADD  vgid INT, CONSTRAINT FK_RepairParts FOREIGN KEY (vgid) REFERENCES VehicleInGarage(vgid)--OR TO CREATE A NEW TABLE\
GO
CREATE OR ALTER PROCEDURE uspDropFKRepairParts AS ALTER TABLE RepairParts DROP CONSTRAINT FK_RepairParts,COLUMN vgid

GO
CREATE OR ALTER PROCEDURE uspAddCKVehicle AS ALTER TABLE Vehicle ADD CONSTRAINT Candidate_Price UNIQUE (price)
GO
CREATE OR ALTER PROCEDURE uspDropCKVehicle AS ALTER TABLE Vehicle DROP CONSTRAINT Candidate_Price

GO 
CREATE OR ALTER PROCEDURE uspAddTableMechanics AS CREATE TABLE Mechanics (
name varchar(20),
pin varchar(5) NOT NULL,
salary int
)
GO
CREATE OR ALTER PROCEDURE uspDropTableMechanics AS DROP TABLE Mechanics

GO

CREATE OR ALTER PROCEDURE uspAddPKMechanics AS ALTER TABLE Mechanics ADD CONSTRAINT PK_Mechanics PRIMARY KEY(pin)
GO 
CREATE OR ALTER PROCEDURE uspDropPKTMechanics AS ALTER TABLE Mechanics DROP CONSTRAINT PK_Mechanics

select *
from StoredProcedures

INSERT INTO StoredProcedures
VALUES('uspSetSlotsToVarchar','uspSetSlotsToInt',1),
('uspAddTelephoneToClient','uspDropTelephoneClient',2),
('uspAddConstraintGoodCredit','uspDropConstraintGoodCredit',3),
('uspAddFKRepairParts','uspDropFKRepairParts',4),
('uspAddCKVehicle','uspDropCKVehicle',5),
('uspAddTableMechanics','uspDropTableMechanics',6),
('uspAddPKMechanics','uspDropPKTMechanics',7)

update CrtVersion
set version=2
select *
from Client
GO
CREATE OR ALTER PROCEDURE goToTargetVersion(@newVersion int) as
BEGIN
	declare @curent int
	declare @var varchar(40)
	set @curent=(select version from CrtVersion)
	if @newVersion<0
		raiserror('NOT A VERSION',10,1)
	if @newVersion>7
		raiserror('NOT A VERSION',10,1)
	
	while @curent >@newVersion	begin
		select @var=uspDown	from StoredProcedures where targetVersion=@curent
		exec (@var)
		set @curent=@curent-1
	end
	while @curent<@newVersion begin
		set @curent=@curent+1
		select @var=uspUp from StoredProcedures where targetVersion=@curent
		exec(@var) 
	end
	update CrtVersion set version=@newVersion
END;

execute goToTargetVersion 1
select *
from Mechanics
drop Table Mechanics
select *
from CrtVersion
drop procedure goToTargetVersion

exec uspDropTelephoneClient

GO 
ALTER PROCEDURE goToTargetVersion(@newVersion int) as
BEGIN
	declare @curent int
	declare @var varchar(40)
	set @curent=(select version from CrtVersion)

	if @newVersion>7
		raiserror('NOT A VERSION',10,1)
	if @newVersion<0
		raiserror('NOT A VERSION',10,1)
	while @curent >@newVersion	begin
		PRINT 'Current Version: ' + Convert(varchar(10),@curent)
		select @var=uspDown	from StoredProcedures where targetVersion=@curent
		PRINT 'Stored Procedure Name: ' + Convert(varchar(50),@var)
		exec (@var)
		set @curent=@curent-1
	end
	while @curent<@newVersion begin
		PRINT 'Current Version: ' + Convert(varchar(10),@curent)
		set @curent=@curent+1
		select @var=uspUp from StoredProcedures where targetVersion=@curent
		PRINT 'Stored Procedure Name: ' + Convert(varchar(50),@var)
		exec(@var) 
		PRINT 'Current Version: ' + Convert(varchar(10),@curent)
		PRINT 'BREAK'
    
	end
	update CrtVersion set version=@newVersion
END;
select *
from StoredProcedures
where targetVersion=1


-- 