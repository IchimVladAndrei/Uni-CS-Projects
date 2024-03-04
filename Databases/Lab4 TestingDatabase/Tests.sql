USE [Chain of Car Dealerships]
GO
CREATE OR ALTER PROCEDURE CreateTest @name VARCHAR(50) AS
BEGIN
	IF EXISTS(SELECT * FROM Tests T WHERE Name=@name)
		BEGIN
			PRINT 'TEST ALREADY EXISTS'
			RETURN
		END

	INSERT INTO Tests(Name) VALUES (@name)
END

EXEC CreateTest 'FirstTest'
select* from Tests


GO
CREATE OR ALTER PROCEDURE AddTableToTestTable @tableName VARCHAR(50) AS
BEGIN 
	IF NOT EXISTS(SELECT * FROM sys.tables WHERE name=@tableName)
	BEGIN
		PRINT 'TABLE '+@tableName+' doesnt exists'
		RETURN 
	END
	IF EXISTS(SELECT * FROM Tables T WHERE T.Name=@tableName)
	BEGIN
		PRINT 'TABLE '+@tableName+' already exists'
		RETURN
	END
	INSERT INTO Tables(Name) VALUES(@tableName)
END



GO
CREATE OR ALTER PROCEDURE RelateTestTables @tableName VARCHAR(50),@testName VARCHAR(50),@noRows INT, @position INT AS
BEGIN 
	IF @position<0
		BEGIN
			PRINT 'Position has to be >0'
			RETURN
		END
	IF @noRows<0
		BEGIN
			PRINT 'NoOfRows has to be >0'
			RETURN
		END

	DECLARE @testID INT, @tableID INT
	SET @testID=(SELECT T.TestID FROM Tests T WHERE T.Name=@testName)
	SET @tableID=(SELECT T.TableID FROM Tables T WHERE T.Name=@tableName)

	INSERT INTO TestTables(TestID,TableID,NoOfRows,Position) VALUES  ---
						(@testID,@tableID,@noRows,@position)
END


GO
CREATE OR ALTER PROCEDURE AddViewToTestTable @viewName VARCHAR(50) AS
BEGIN
	IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.VIEWS WHERE TABLE_NAME=@viewName)
	BEGIN
		PRINT 'View '+@viewName+' doesnt exist'
		RETURN
	END
	IF EXISTS(SELECT * FROM Views WHERE Name=@viewName)
	BEGIN
		PRINT 'View already added'
		RETURN
	END
	INSERT INTO Views(Name) VALUES (@viewName)
END


GO 
CREATE OR ALTER PROCEDURE RelateTestsAndViews @viewName VARCHAR(50),@testName VARCHAR(50) AS
BEGIN
	DECLARE @testID INT,@viewID INT
	SET @testID=(SELECT TestID FROM Tests T WHERE T.Name=@testName)
	SET @viewID=(SELECT ViewID FROM Views V WHERE V.Name=@viewName)
	INSERT INTO TestViews(TestID,ViewID) VALUES (@testID,@viewID)
END

GO
CREATE OR ALTER PROCEDURE RunTest @name VARCHAR(50) AS 
BEGIN
	DECLARE @test INT
	SET @test=(SELECT T.TestID FROM Tests T WHERE T.Name=@name)

	DECLARE @tableName VARCHAR(50),@noRows INT,@tableID INT,
			@viewName VARCHAR(50),@viewID INT,
			@testRunID INT,@command VARCHAR(256),
			@curentTestStart DATETIME2,@curentTestEnd DATETIME2,
			@allTestsStart DATETIME2,@allTestEnd DATETIME2

	INSERT INTO TestRuns(Description) Values (@name)
	SET @testRunID=CONVERT(INT,(SELECT last_value FROM sys.identity_columns WHERE name='TestRunId'))

	DECLARE TablesCursor CURSOR SCROLL FOR
	SELECT T2.TableID,T2.Name,TT.NoOfRows
	FROM TestTables TT
	INNER JOIN Tables T2 ON T2.TableID=TT.TableID
	WHERE TT.TestID=@test
	ORDER BY TT.Position

	DECLARE ViewsCursor CURSOR FOR
	SELECT V.ViewID, V.Name
	FROM Views V
	INNER JOIN TestViews TV ON TV.ViewID=V.ViewID
	WHERE TV.TestID=@test

	SET @allTestsStart=SYSDATETIME();

	OPEN TablesCursor
	FETCH FIRST FROM TablesCursor 
	INTO @tableID,@tableName,@noRows

	WHILE @@FETCH_STATUS=0 --populate
	BEGIN
		SET @curentTestStart=SYSDATETIME();
		SET @command='PopulateTable '+char(39)+@tableName+char(39)+','+CONVERT(VARCHAR(10),@noRows)--char(39) => simple quote
		PRINT @noRows
		EXEC (@command)
		SET @curentTestEnd=SYSDATETIME();
		INSERT INTO TestRunTables VALUES (@testRunID,@tableID,@curentTestStart,@curentTestEnd)
		FETCH NEXT FROM TablesCursor INTO @tableId,@tableName,@noRows
	END
	CLOSE TablesCursor
	
	
	OPEN ViewsCursor
	FETCH FROM ViewsCursor INTO @viewID,@viewName
	WHILE @@FETCH_STATUS=0
		BEGIN
			SET @curentTestStart=SYSDATETIME();
			DECLARE @statement VARCHAR(256)
			SET @statement='SELECT * FROM '+@viewName
			PRINT @statement
			EXEC (@statement)
			SET @curentTestEnd=SYSDATETIME();
			INSERT INTO TestRunViews VALUES(@testRunID,@viewID,@curentTestStart,@curentTestEnd)
			FETCH NEXT FROM ViewsCursor INTO @viewID,@viewName
		END
	CLOSE ViewsCursor
	DEALLOCATE ViewsCursor

		OPEN TablesCursor
		FETCH LAST FROM TablesCursor INTO @tableID,@tableName,@noRows

		WHILE @@FETCH_STATUS=0 --clear
		BEGIN
			EXEC ClearTable @tableName 
			FETCH PRIOR FROM TablesCursor INTO @tableID,@tableName,@noRows
		END 
		CLOSE TablesCursor
		DEALLOCATE TablesCursor
	SET @allTestEnd=SYSDATETIME();
	
	UPDATE TestRuns
		SET StartAt=@allTestsStart,EndAt=@allTestEnd
		WHERE TestRunID=@testRunID
END 


SELECT * FROM Views
SELECT * FROM Tables
SELECT * FROM TestViews
SELECT * FROM Tests
SELECT * FROM TestTables 
SELECT * FROM TestRunTables
SELECT * FROM TestRuns
SELECT * FROM TestRunViews

/*TEST 1
TABLES: Client*
views AtPension
*/
EXEC CreateTest 'SmallTest'
EXEC AddTableToTestTable 'Client'
EXEC RelateTestTables 'Client','SmallTest',150,0
EXEC AddViewToTestTable 'AtPension'
EXEC RelateTestsAndViews 'AtPension','SmallTest'
EXEC RunTest 'SmallTest' 

/*TEST 2
TABLES: RefferalType*,Garage,Client
views ClientRefferal
*/

EXEC CreateTest'SmallTest2'
EXEC AddTableToTestTable 'RefferalType'
EXEC AddTableToTestTable 'Garage'
EXEC RelateTestTables 'Client','SmallTest2',150,0
EXEC RelateTestTables 'RefferalType','SmallTest2',100,1 
EXEC RelateTestTables 'Garage','SmallTest2',200,2
EXEC AddViewToTestTable 'ClientRefferal'
EXEC RelateTestsAndViews 'ClientRefferal','SmallTest2'  
EXEC RunTest 'SmallTest2'

/*TEST 3 
TABLES: PartsPayment*,Garage,Payment Transaction,RepairParts
views paymentGarages
*/

EXEC CreateTest 'SmallTest3'
EXEC AddTableToTestTable 'PartsPayment'
EXEC AddTableToTestTable 'RepairParts'
EXEC AddTableToTestTable 'PaymentTransaction'
EXEC RelateTestTables 'PartsPayment','SmallTest3',140,3 
EXEC RelateTestTables 'Garage','SmallTest3',200,0
EXEC RelateTestTables 'RepairParts','SmallTest3',140,1
EXEC RelateTestTables 'PaymentTransaction','SmallTest3',140,2
EXEC AddViewToTestTable 'PaymentGarages'
EXEC RelateTestsAndViews 'PaymentGarages','SmallTest3'
exec RunTest 'SmallTest3'