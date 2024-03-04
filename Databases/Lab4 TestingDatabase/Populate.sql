USE [Chain of Car Dealerships]
GO
CREATE VIEW Randomizer
AS
SELECT RAND() AS Value

GO
CREATE FUNCTION dbo.RandomInt(@lower INT,@upper INT) RETURNS INT AS
BEGIN
	RETURN FLOOR((SELECT Value FROM Randomizer)*(@upper-@lower)+@lower);
END

GO
CREATE OR ALTER PROCEDURE InsertClient @aux INT AS
BEGIN
	INSERT INTO Client 
	VALUES (@aux,'Andrei'+CONVERT(VARCHAR(50),@aux),'Pop'+CONVERT(VARCHAR(50),@aux),dbo.RandomInt(18,70),CONVERT(bit,dbo.RandomInt(0,1)))
END

GO
CREATE OR ALTER PROCEDURE InsertGarage @aux INT AS
BEGIN
	DECLARE @allSlots INT
	DECLARE @emptySlots INT
	SET @allSlots=dbo.RandomInt(0,100)
	SET @emptySlots=dbo.RandomInt(0,@allSlots)

	INSERT INTO Garage 
	VALUES(@aux,(SELECT TOP 1 did FROM Dealership),@allSlots,@emptySlots)-- 
END
go
CREATE OR ALTER PROCEDURE InsertRefferalType @aux INT AS
BEGIN
	INSERT INTO RefferalType
	VALUES (@aux,dbo.RandomInt(0,@aux),dbo.RandomInt(0,3))
END

GO
CREATE OR ALTER PROCEDURE InsertPaymentTransaction @aux INT AS
BEGIN
	INSERT INTO PaymentTransaction
	VALUES (@aux,(select top 1 gid from Garage),dbo.RandomInt(150,2000))
END

GO 
CREATE OR ALTER PROCEDURE InsertRepairParts @aux INT AS
BEGIN
	INSERT INTO RepairParts
	VALUES (@aux,(select top 1 gid from Garage),'Wheels'+CONVERT(VARCHAR(50),@aux))
END

GO
CREATE OR ALTER PROCEDURE InsertPartsPayment @aux INT AS
BEGIN
	declare @partId INT,@priceId INT
	WHILE 1=1
	BEGIN 
		set @partId=(select top 1 id from RepairParts order by newid())
		set @priceId=(select top 1 id from PaymentTransaction order by newid())
		IF NOT EXISTS(SELECT 1 FROM PartsPayment WHERE partId=@partId and priceId=@priceId)
			BREAK
	END
	INSERT INTO PartsPayment
		VALUES (@partId,@priceId)

END


GO
CREATE OR ALTER PROCEDURE PopulateTable @tableName VARCHAR(50),@noRows INT AS
BEGIN
	DECLARE @curentRow INT,@command VARCHAR(256)
	SET @curentRow=0
	WHILE @curentRow<@noRows
		BEGIN
			SELECT @command='Insert'+@tableName+' '+CONVERT(VARCHAR(10),@curentRow)
			EXEC (@command)
			SET @curentRow=@curentRow+1
		END
END

GO
CREATE OR ALTER PROCEDURE ClearTable @tableName VARCHAR(50) as
	EXEC ('DELETE FROM '+@tableName)

GO--ALL CLIENTS THAT LIVE ON A PENSION
CREATE VIEW AtPension AS
SELECT C.first_name,C.last_name
FROM Client C
WHERE C.age>60


GO --See who reffered them here
CREATE VIEW ClientRefferal AS
SELECT DISTINCT C.first_name,C.last_name,RT.type
FROM Client C
INNER JOIN RefferalType RT ON C.cid=RT.cid


GO --see what are the most common sums to be spend
CREATE VIEW PaymentGarages AS
SELECT PT.sum,COUNT(G.gid) as Garages
FROM PaymentTransaction PT
INNER JOIN Garage G ON G.gid=PT.gid
GROUP BY PT.sum
go
--see how many dealerships group by number of slots 
select * from RefferalType
select * from Client
select * from Garage
exec PopulateTable 'Garage',10
exec ClearTable 'Client'
exec ClearTable 'Garage'




/*

*/

select * from PartsPayment
select * from PaymentTransaction
select * from Garage
select * from RepairParts
alter table RepairParts
Drop column price
exec PopulateTable 'PartsPayment',10
exec PopulateTable 'RepairParts',10
exec PopulateTable 'Garage',10
exec PopulateTable 'PaymentTransaction',10
exec ClearTable 'PartsPayment'
exec ClearTable 'Garage'
exec ClearTable 'RepairParts'
exec ClearTable 'PaymentTransaction'