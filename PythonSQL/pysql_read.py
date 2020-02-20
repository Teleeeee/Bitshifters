import mysql.connector
from mysql.connector import Error
from dotenv import load_dotenv
import os

load_dotenv()
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

    sql_select_Query = "SELECT * FROM logs"
    cursor = connection.cursor()
    cursor.execute(sql_select_Query)
    records = cursor.fetchall()
    print("Total number of rows in logs is: ", cursor.rowcount)

    print("\nPrinting each log entry")
    for row in records:
        print("Id = ", row[0], )
        print("Type = ", row[1])
        print("Confidence  = ", row[2])
        print("Date  = ", row[3])
        print("Time  = ", row[4], "\n")

except Error as e:
    print("Error while connecting to MySQL", e)
finally:
    if (connection.is_connected()):
        cursor.close()
        connection.close()
        print("MySQL connection is closed")