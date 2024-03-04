
use [Chain of Car Dealerships]
GO
--select all vehicle brands within the Franchise
SELECT DISTINCT F.brand
FROM Factory F
UNION ALL
SELECT V.brand_model
FROM Vehicle V

SELECT COUNT(*) AS 'Growing businesses'
FROM Dealership D
WHERE D.available_cars> DATEDIFF(year, D.opening_date,'2023/10/22')*200 OR D.no_garages>10

--------------
--dealerships that have garage data 
SELECT D.did 'Dealership'
FROM Dealership D
INTERSECT
SELECT G.did 
FROM Garage G

--BRANDS that are faulty
SELECT V.brand_model
FROM Vehicle V
WHERE V.vin IN (
	SELECT VG.vin
	FROM VehicleInGarage VG
	)
-- WITH IN operator
----
SELECT *
FROM RepairParts

------------
-- clients that dont have a leasing
SELECT C.first_name
FROM Client C
WHERE C.cid IN(
	SELECT C1.cid 
	FROM Client C1
	EXCEPT
	SELECT L.cid 
	FROM Leasing L)
--dealerships that dont have garage data
SELECT D.location
FROM Dealership D
WHERE D.did NOT IN(
	SELECT G.did
	FROM Garage G)
--------------d
--empty slots of garages that have repair parts
SELECT DISTINCT G.empty_slots,G.gid AS 'Garage'
FROM Garage G
INNER JOIN RepairParts RP 
ON G.gid=RP.gid

--what age does result in a good credit in a leasing 3tables
SELECT *
FROM Client C
JOIN Leasing L ON C.cid=L.cid
JOIN Vehicle V ON L.vin=V.vin
ORDER BY C.age ASC
--left clients that may have a leasing
SELECT *
FROM Client C
LEFT JOIN Leasing L ON L.cid=C.cid
--right  show top 3 locations with the greatest monthly leasing payments 
SELECT TOP 3 *
FROM Dealership D
RIGHT JOIN Leasing L ON L.did=D.did 
ORDER BY L.monthly_value

--full  Show brands and their typical repair time
SELECT *
FROM Vehicle V 
FULL JOIN VehicleInGarage VG  ON  VG.vin=V.vin
ORDER BY VG.repair_time DESC
--2m:n show all factories contract days on whose dealership that have client withat least ..no contracts
--SHOW THE HEAD MANAGER OF THOSE FACTORIES THAT DELIVER CARS TO THOSE DEALERSHIPs WITH CLIENTS WITH AT LEAST 2 CONTRACTS
SELECT DISTINCT F.head_manager
FROM Factory F
INNER JOIN WorksWith WW ON F.fid=WW.fid
INNER JOIN Dealership D ON WW.did=D.did
INNER JOIN IsCustomer IC ON IC.did=D.did
INNER JOIN Client C ON IC.cid=C.cid
WHERE IC.no_cotracts>1
-------
--the average age of clients with good credit
SELECT AVG(q.cred) as 'Average age'
FROM (
	SELECT AVG(C.age) as cred
	FROM Client C
	WHERE C.good_credit=1
)AS q
--the number of total leases
SELECT q.total_leases
FROM(
	SELECT COUNT(*) AS total_leases
	FROM Leasing L
	JOIN Client C ON C.cid=L.cid

)AS q

--- see the factory brands that workwith dealerships with garages with more than 8 slots

SELECT F.brand, F.employees_no
FROM Factory F
WHERE F.did  IN(
	SELECT D.did
	FROM Dealership D
	WHERE D.did IN(
		SELECT G.did
		FROM Garage G
		WHERE G.slots>8
	)
)
--see managers with cars in need of service until 2025
SELECT F.head_manager
FROM Factory F
WHERE F.brand IN (
	SELECT V.brand_model
	FROM Vehicle V
	WHERE V.next_service<'2025-01-01'
)
-------------
--does a vehicles in a leasing have monthly value at least 1500
SELECT V.vehicle_type,V.fuel_efficiency
FROM Vehicle V
WHERE EXISTS
	(SELECT L.co_id
	FROM Leasing L
	WHERE V.vin=L.vin AND L.monthly_value>1500)

--there are employees working for a brand with a short contract <1year?
SELECT F.employees_no,F.brand
FROM Factory F
WHERE EXISTS(
	SELECT WW.fid
	FROM WorksWith WW
	WHERE WW.period_contract_days<=365
)
----
SELECT COUNT(C.cid) 'number of people',C.age
FROM Client C
GROUP BY C.age

--dealerships with cars at least half of the max
SELECT D.available_cars,D.location
FROM Dealership D
GROUP BY D.available_cars,D.location
HAVING D.available_cars>=(SELECT MAX(D.available_cars)/2 FROM Dealership D)
ORDER BY D.available_cars DESC --see having
--top 3 brands that have fuel efficiency better than average
SELECT TOP 3 V.brand_model,V.fuel_efficiency
FROM Vehicle V
GROUP BY V.fuel_efficiency,V.brand_model
HAVING V.fuel_efficiency<=(SELECT AVG(V.fuel_efficiency) FROM Vehicle V)
--there is a leasing with value at leas a third of all leasings
SELECT L.monthly_value,L.co_id,L.sign_date,L.end_date
FROM Leasing L
GROUP BY L.monthly_value,L.co_id,L.sign_date,L.end_date
HAVING L.monthly_value>(SELECT SUM(L.monthly_value)/3 FROM Leasing L)
---------
--clients with at least a contract
SELECT C.cid,C.first_name,C.last_name
FROM Client C
WHERE cid=ANY(SELECT L.cid FROM Leasing L)

SELECT C.cid,C.first_name,C.last_name
FROM Client C
WHERE cid IN (SELECT L.cid FROM Leasing L)

--show clients and their age of clients with good credit whose age is higher than the age of all clients with poor credit
SELECT C.cid,C.first_name,C.last_name
FROM Client C
WHERE C.age>ALL(
	SELECT C.age
	FROM Client C
	WHERE C.good_credit=0
)
SELECT C.cid,C.first_name,C.last_name
FROM Client C
WHERE C.age>(SELECT MAX(c.age) FROM Client c WHERE c.good_credit=0)

--show cars that are in service for less than 40days
SELECT V.brand_model,V.price
FROM Vehicle V
WHERE V.vin=ANY(SELECT VIG.vin FROM VehicleInGarage VIG WHERE VIG.repair_time<40)
SELECT V.brand_model,V.price
FROM Vehicle V
WHERE V.vin IN (SELECT VIG.vin FROM VehicleInGarage VIG WHERE VIG.repair_time<40)


--show the repair parts that has a greater price than some parts with price <350
SELECT R.price,R.type
FROM RepairParts R
WHERE R.price >ALL(SELECT price FROM RepairParts WHERE price <350)

--see leasing values of some clients with good credit and age >30
SELECT L.monthly_value
FROM Leasing L
WHERE L.cid=ANY(SELECT C.cid FROM Client C WHERE C.good_credit=1 AND c.age>30)


select *
from RepairParts D

INSERT IsCustomer(id,did,no_cotracts,cid)
VALUES 
(7,1,3,3),
(32,3,2,6),
(49,3,3,4),
(12,4,1,2),
(14,1,1,5),
(55,3,1,1)