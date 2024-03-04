use [Chain of Car Dealerships]
CREATE TABLE Model
(
mid INT PRIMARY KEY,--aid
year INT UNIQUE,--a2
modelName VARCHAR(30)
)
CREATE TABLE Brand(
bid INT PRIMARY KEY,--bid
brandType INT,--b2
brandName VARCHAR(20)
)
CREATE TABLE ModelOption
(moid INT PRIMARY KEY,--cid
mid INT REFERENCES Model(mid),--aid
bid INT REFERENCES Brand(bid)--bid
)

CREATE OR ALTER PROCEDURE InsertModel @aux INT AS
BEGIN
	DECLARE @year INT
	
	WHILE 1=1
	BEGIN
		SET @year=dbo.RandomInt(0,99999)
		IF NOT EXISTS(SELECT 1 FROM Model WHERE year=@year)
			BREAK
	END
	INSERT INTO Model
	VALUES (@aux,@year,'Logan'+CONVERT(VARCHAR(50),@aux))
END 


CREATE OR ALTER PROCEDURE InsertBrand @aux INT AS
BEGIN
	INSERT INTO Brand
	VALUES(@aux,dbo.RandomInt(1,10),'Dacia'+CONVERT(VARCHAR(50),@aux))
END 
CREATE OR ALTER PROCEDURE InsertModelOption @aux INT AS
BEGIN
	INSERT INTO ModelOption
	VALUES(@aux,(select top 1 mid from Model order by newid()),(select top 1 bid from Brand order by NEWID()))
END 

EXEC PopulateTable 'Model',9999
EXEC PopulateTable 'Brand',2500
EXEC PopulateTable 'ModelOption',4000

select * from Model --clustered index scan
SELECT *
FROM Model
WHERE mid>2000		--clustered index seek

SELECT year			--nonClustered index scan by default
FROM Model
ORDER BY year
DROP INDEX IF EXISTS ModelNonClusteredIndex ON Model
CREATE NONCLUSTERED INDEX ModelNonClusteredIndex ON Model(year)

SELECT year				--nonClustered index seek
FROM Model
WHERE year >1000 AND year <7000

SELECT modelName	--key lookup
FROM Model
WHERE year=2023
--0,002907 without,  0,0004985 with index
SELECT *
FROM Brand
WHERE brandType=7
 DROP INDEX IF EXISTS BrandNonClusteredIndex ON Brand

CREATE NONCLUSTERED INDEX BrandNonClusteredIndex ON Brand(brandType) INCLUDE (brandName)

CREATE OR ALTER VIEW Lab5 AS
SELECT TOP 1000 M.modelName, B.brandName
FROM ModelOption MO
	INNER JOIN Model M ON M.mid=MO.mid
	INNER JOIN Brand B ON B.bid=MO.bid
WHERE M.year>2000
ORDER BY B.brandType
--0,420374 fara   0,419633 cu previous Index 0,418151 si cu indexspecial
SELECT * FROM Lab5
--prev index helps us
CREATE NONCLUSTERED INDEX ModelNonClusteredIndex ON ModelOption(moid) INCLUDE (mid,bid)
 DROP INDEX IF EXISTS ModelNonClusteredIndex ON ModelOption