

use [Chain of Car Dealerships]
CREATE TABLE Factory(
fid INT PRIMARY KEY,
brand VARCHAR(15),
employees_no INT,
head_manager VARCHAR(20)
)



CREATE TABLE Dealership(
did INT PRIMARY KEY,
location VARCHAR(25) NOT NULL,
available_cars INT,
no_garages INT DEFAULT 1,
opening_date DATE
)

CREATE TABLE Client(
cid INT PRIMARY KEY,
last_name VARCHAR(25) NOT NULL,
first_name VARCHAR(25),
age INT,
good_credit BIT
)

CREATE TABLE Vehicle(
vin INT PRIMARY KEY,
brand_model VARCHAR(15),
price INT,
fuel_efficiency DECIMAL(4,2),
vehicle_type VARCHAR(10),
next_service DATE
)

CREATE TABLE Leasing(
co_id INT PRIMARY KEY,
vin INT REFERENCES Vehicle(vin),
cid INT REFERENCES Client(cid),
sign_date DATE,
end_date DATE,
monthly_value SMALLINT,
interest_rate TINYINT
)ALTER TABLE Leasing
DROP CONSTRAINT FK_Leasing_CID
ALTER TABLE Leasing
ADD CONSTRAINT FK_Leasing_CID
FOREIGN KEY (cid)-- AM DAT DELETE LA ASTA 
REFERENCES Client(cid) --dau delete la coloana cid care e acum si adaug alta ca o sa fie noul foreign
						-- key cu on delete cascade
ON DELETE CASCADE

ALTER TABLE Factory
ADD did INT REFERENCES Dealership(did)

CREATE TABLE Garage(
gid INT PRIMARY KEY,
did INT REFERENCES Dealership(did),
slots TINYINT,
empty_slots TINYINT
)

CREATE TABLE VehicleInGarage(
vgid INT PRIMARY KEY,
gid INT REFERENCES Garage(gid),
vin INT REFERENCES Vehicle(vin),
check_in DATE,
repair_time TINYINT
)
ALTER TABLE VehicleInGarage
DROP CONSTRAINT FK__VehicleInGa__gid__534D60F1
ALTER TABLE VehicleInGarage
ADD CONSTRAINT FK_VIG_GID
FOREIGN KEY (gid) REFERENCES Garage(gid)
ON DELETE CASCADE

CREATE TABLE WorksWith(
id INT PRIMARY KEY,
fid INT REFERENCES Factory(fid),
did INT REFERENCES Dealership(did),
period_contract_days SMALLINT
)


CREATE TABLE IsCustomer(
id INT PRIMARY KEY,
cid INT REFERENCES Client(cid) UNIQUE,
did INT REFERENCES Dealership(did),
no_cotracts TINYINT,

)
ALTER TABLE IsCustomer
DROP CONSTRAINT FK__IsCustomer__cid__70DDC3D8 --DROP LA FOREIGN KEY

ALTER TABLE IsCustomer
ADD CONSTRAINT FK_IC_CID -- am dat clear la table sa pot adauga constraintul
FOREIGN KEY (cid) 
REFERENCES Client(cid)
ON DELETE CASCADE

CREATE TABLE RepairParts(
id INT PRIMARY KEY,
gid INT REFERENCES Garage(gid),
price SMALLINT,
type VARCHAR(20),

)
ALTER TABLE RepairParts
DROP CONSTRAINT FK__RepairParts__gid__5EBF139D
ALTER TABLE RepairParts
ADD CONSTRAINT FK_RP_GID
FOREIGN KEY (gid) REFERENCES Garage(gid)
ON DELETE CASCADE

CREATE TABLE RefferalType
(id INT PRIMARY KEY,
 cid INT,
 type INT,
 CONSTRAINT FK_RT_CID 
 FOREIGN KEY (cid) REFERENCES Client(cid)
ON DELETE CASCADE
)
CREATE TABLE PartsPayment
(partId int references RepairParts(id),
priceId int references PaymentTransaction(id),
primary key (partId,priceId)
)
CREATE TABLE PaymentTransaction(
id INT PRIMARY KEY,
gid INT,
sum INT,
CONSTRAINT FK_PT_GID
FOREIGN KEY (gid)
REFERENCES Garage(gid)
ON DELETE CASCADE
)