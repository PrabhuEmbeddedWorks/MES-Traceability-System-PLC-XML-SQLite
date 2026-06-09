# MES Traceability System (PLC → XML → SQLite)

A Linux-based **Manufacturing Execution System (MES)** simulation developed in **C** that demonstrates end-to-end manufacturing traceability. The project uses a **Virtual PLC** to generate machine data, detects production cycle completion events, creates structured **XML production records**, validates them against an **XSD schema**, and stores validated information in an **SQLite database**.

This project showcases **Industry 4.0 concepts** such as PLC-to-MES communication, quality data logging, XML-based data exchange, and component traceability commonly used in automotive manufacturing environments.

---
## Workflow Summary

1. Virtual PLC updates machine registers.
2. MES detects the cycle completion event.
3. Production data is collected.
4. XML production records are generated.
5. XML files are validated against the XSD schema.
6. Valid records are stored in SQLite.
7. Production history can be queried for traceability.

## Project Architecture

```text
Virtual PLC (C Structure)
        ↓
MES Application (C Program)
        ↓
Generate XML File
        ↓
Validate XML using XSD
        ↓
Store Data in SQLite Database
        ↓
Verify using Linux Terminal
```

---

## Manufacturing Use Case

Consider an automotive production line assembling Electronic Control Units (ECUs). After a manufacturing cycle is completed, machine data such as:

* PCB Serial Number
* Peak Torque Applied
* Operator ID
* Production Timestamp
* Cycle Completion Status

must be captured and stored for future quality audits and traceability requirements.

This project simulates that workflow.

---

## Features

* Virtual PLC register simulation
* MES cycle completion detection
* XML generation from machine data
* XML validation using XSD schema
* SQLite database integration
* Manufacturing traceability logging
* Linux terminal-based execution
* Industry 4.0 inspired architecture

---

## Technologies Used

| Technology    | Purpose                  |
| ------------- | ------------------------ |
| C Programming | MES application logic    |
| Ubuntu 22.04  | Development environment  |
| SQLite        | Traceability database    |
| XML           | Production data exchange |
| XSD           | XML validation           |
| GCC           | Compilation              |
| xmllint       | XML schema validation    |

---

## Project Structure

```text
MES-Traceability-System-PLC-XML-SQLite/
│
├── mes_logger.c          # MES application source code
├── production.xsd        # XML schema definition
├── production.xml        # Generated XML file
├── production.db         # SQLite database
├── mes_logger            # Executable binary
└── README.md             # Project documentation
```

---

## Prerequisites

Install the required packages:

```bash
sudo apt update

sudo apt install build-essential -y

sudo apt install sqlite3 libsqlite3-dev -y

sudo apt install libxml2 libxml2-dev -y

sudo apt install libxml2-utils -y
```

Verify installation:

```bash
gcc --version

sqlite3 --version

xmllint --version
```

---

## Database Setup

Create the SQLite database:

```bash
sqlite3 production.db
```

Execute the following SQL commands:

```sql
CREATE TABLE ProductionLog
(
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    SerialNumber TEXT NOT NULL,
    Torque REAL NOT NULL,
    OperatorID INTEGER NOT NULL,
    Timestamp TEXT NOT NULL
);

.tables

.quit
```

---

## XML Schema Setup

Create the schema file:

```bash
nano production.xsd
```

Paste the XSD definition and save the file.

---

## Compilation

Compile the MES application:

```bash
gcc mes_logger.c -o mes_logger -lsqlite3
```

---

## Running the Application

Execute the program:

```bash
./mes_logger
```

---

## Expected Console Output

```text
MES Started...
Cycle Complete Detected
XML Generated
SQLite Updated
```

---

## Generated XML Output

Example:

```xml
<?xml version="1.0"?>

<ProductionData>

    <SerialNumber>PCB1001</SerialNumber>

    <Torque>5.25</Torque>

    <OperatorID>102</OperatorID>

    <Timestamp>2026-06-09 11:20:15</Timestamp>

</ProductionData>
```

---

## XML Validation

Validate the generated XML against the schema:

```bash
xmllint --schema production.xsd production.xml --noout
```

Successful validation:

```text
production.xml validates
```

---

## Database Verification

View the stored records:

```bash
sqlite3 production.db
```

Inside SQLite:

```sql
.headers on

.mode column

SELECT * FROM ProductionLog;

.quit
```

Example output:

```text
ID  SerialNumber  Torque  OperatorID  Timestamp
--  ------------  ------- ---------- -------------------
1   PCB1001       5.25    102         2026-06-09 11:20:15
```

---

## Skills Demonstrated

* Embedded C Programming
* Linux Development
* SQLite Database Integration
* XML Data Handling
* XSD Validation
* Manufacturing Traceability Concepts
* MES Fundamentals
* Quality Logging Techniques
* Industry 4.0 Principles

---

