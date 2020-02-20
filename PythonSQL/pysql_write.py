import mysql.connector
from mysql.connector import Error
from dotenv import load_dotenv
import os
import txt_parser

load_dotenv()
logs = txt_parser.readLog("random.txt")
try:
    connection = mysql.connector.connect(host=os.environ.get('RDS_HOST'),
                                         database=os.environ.get('RDS_DATABASE'),
                                         user=os.environ.get('RDS_USER'),
                                         password=os.environ.get('RDS_PASSWORD'))
    if connection.is_connected():
        db_Info = connection.get_server_info()
        print("Connected to MySQL Server version ", db_Info)
        cursor = connection.cursor()
        cursor.execute("select database();")
        record = cursor.fetchone()
        print("You're connected to database: ", record)

    for log in logs:
        mySql_insert_query = ("INSERT INTO logs2 (date, time, person_count, dog_count) VALUES (\"" + 
                              log.date + "\" , \"" + log.time + "\" , \"" + str(log.cntPerson) + 
                              "\", \"" + str(log.cntDogs) + "\")")
        cursor = connection.cursor()
        cursor.execute(mySql_insert_query)
        connection.commit()
        print(cursor.rowcount, "Record inserted successfully into logs.")
        cursor.close()

except Error as e:
    print("Error while connecting to MySQL", e)
finally:
    if (connection.is_connected()):
        cursor.close()
        connection.close()
        print("MySQL connection is closed")