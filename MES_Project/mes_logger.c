#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>

typedef struct
{
    char serial_no[20];
    float torque;
    int operator_id;
    int cycle_complete;

} PLC_Register;

PLC_Register plc;

void write_machine_registers()
{
    strcpy(plc.serial_no, "PCB1001");

    plc.torque = 5.25;

    plc.operator_id = 102;

    plc.cycle_complete = 1;
}

void generate_xml(char *timestamp)
{
    FILE *fp = fopen("production.xml", "w");

    fprintf(fp,
"<?xml version=\"1.0\"?>\n");

    fprintf(fp,
"<ProductionData>\n");

    fprintf(fp,
"    <SerialNumber>%s</SerialNumber>\n",
plc.serial_no);

    fprintf(fp,
"    <Torque>%.2f</Torque>\n",
plc.torque);

    fprintf(fp,
"    <OperatorID>%d</OperatorID>\n",
plc.operator_id);

    fprintf(fp,
"    <Timestamp>%s</Timestamp>\n",
timestamp);

    fprintf(fp,
"</ProductionData>\n");

    fclose(fp);
}

void update_database(char *timestamp)
{
    sqlite3 *db;

    char *errmsg = 0;

    char sql[500];

    sqlite3_open("production.db", &db);

    sprintf(sql,

"INSERT INTO ProductionLog "
"(SerialNumber,Torque,OperatorID,Timestamp) "
"VALUES('%s',%.2f,%d,'%s');",

plc.serial_no,
plc.torque,
plc.operator_id,
timestamp);

    sqlite3_exec(db,
                 sql,
                 0,
                 0,
                 &errmsg);

    sqlite3_close(db);
}

int main()
{
    time_t t;

    struct tm *tm_info;

    char timestamp[30];

    printf("MES Started...\n");

    write_machine_registers();

    if(plc.cycle_complete == 1)
    {
        printf("Cycle Complete Detected\n");

        time(&t);

        tm_info = localtime(&t);

        strftime(timestamp,
                 sizeof(timestamp),
                 "%Y-%m-%d %H:%M:%S",
                 tm_info);

        generate_xml(timestamp);

        printf("XML Generated\n");

        update_database(timestamp);

        printf("SQLite Updated\n");
    }

    return 0;
}
