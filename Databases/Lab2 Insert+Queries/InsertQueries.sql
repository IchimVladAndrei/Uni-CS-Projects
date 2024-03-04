use [Chain of Car Dealerships]
go
INSERT Dealership
VALUES
(1,'Suceava',3421,59,'2010-10-04'),
(2,'Iasi',153,7,'2020-09-12'),
(3,'Burdujeni',120,4,'2021-04-24'),
(4,'Nasaud',532,22,'2016-02-20'),
(5,'Dej',221,16,'2019-04-23'),
(6,'Cluj',2341,38,'2014-03-21'),
(7,'Oradea',240,14,'2018-06-15'),
(8,'Timisoara',1604,29,'2015-07-12'),
(9,'Craiova',130,8,'2021-10-10'),
(10,'Ploiesti',49,1,'2022-11-04'),
(11,'Pitesti',30,1,'2023-01-10'),
(12,'Bucuresti',2903,30,'2023-04-28'),
(13,'Constanta',1840,17,'2022-04-10');


INSERT Factory
VALUES 
(1,'Volvo',532,'Kyra Allison',1),
(2,'Mercedes',876,'Solomon Collier',12),
(3,'Bugatti',324,'Yoko Phelps',1),
(4,'Lamborghini',432,'Ivan Levine',1),
(5,'Dacia',1325,'Alexandra Logan',2),
(6,'Skoda',765,'Justina Sweeney',5),
(7,'BMW',978,'Conan Walter',3),
(8,'McLaren',475,'Clementine Copeland',6);

INSERT Dealership
VALUES (14,'Galati',101,4,'2023-10-15');
INSERT WorksWith
VALUES 
(1,1,1,721),
(2,1,3,2300),
(3,1,4,2300);


INSERT Garage
VALUES
(20,999,124,0),
(11,1,21,11),
(5,2,40,null),
(16,12,null,null),
(2,14,31,21),
(3,3,25,10),

(13,4,null,null);
INSERT Vehicle
VALUES 
(5332,'Bugatti',5000000,30.23,'Hyper','2024-10-10'),
(5634,'Bugatti',2300452,25.22,'Hyper','2023-11-12'),
(554,'Volvo',64024,8.92,'SUV','2024-09-23'),
(524,'Volvo',89234,9.11,'SUV','2023-10-19'),
(542,'Volvo',49243,7.44,'Sedan','2025-04-12'),
(565,'Volvo',57294,3.22,'Hybrid','2026-11-03'),
(4667,'Mercedes',78924,2.11,'Electric','2026-01-10'),
(4782,'Mercedes',105332,1.22,'Electric','2026-01-10');


UPDATE Vehicle
SET next_service='2024-01-11'
WHERE price>99999 AND price <=4999999;
UPDATE Vehicle
SET vehicle_type='HyperCar'
WHERE (price>=1000000 AND price<9999999) OR fuel_efficiency>22.00;
UPDATE Vehicle
SET price=price-5000
WHERE next_service BETWEEN '2023-01-01' AND '2024-12-30';


DELETE Vehicle
WHERE vehicle_type='Hybrid' OR vehicle_type LIKE 'S___%'
DELETE Garage
WHERE empty_slots IS NULL
DELETE Garage
WHERE slots=21 
DELETE Dealership
WHERE location IN ('Craiova','Pitesti');


INSERT RepairParts
VALUES
(312,2,3044,'Sideskirts'),
(532,2,1004,'Tires'),
(454,2,53,'Oil'),
(368,3,234,'Sparks'),
(389,3,432,'Display'),
(231,2,6755,'Clutch');

INSERT RepairParts
VALUES 
(416,2,null,'Shifter');


UPDATE RepairParts
SET price=price+price*0.1
WHERE price IS NOT NULL;
UPDATE WW
SET period_contract_days=period_contract_days+period_contract_days*0.15-13
FROM WorksWith WW
WHERE did<>1

SELECT *
FROM Vehicle;

/*Volvo
Mercedes
Bugatti
Lamborghini
Dacia
Skoda
BMW
McLaren*/
---------extra---

INSERT Vehicle
VALUES 
(1568,'BMW',45662,7.42,'Sedan','2025-04-21'),
(1656,'BMW',65429,10.50,'Sport','2025-04-28'),
(2421,'McLaren',300540,20.99,'HyperCar','2024-03-12'),
(989,'Skoda',25040,5.60,'Sedan','2025-05-12'),
(945,'Skoda',21400,5.60,'Sedan','2025-05-16'),
