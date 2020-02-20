import mysql.connector
from mysql.connector import Error
from dotenv import load_dotenv
import os

#load_dotenv()

class LogEntry:
    def __init__(self):
        self.cntPerson = 0
        self.cntDogs = 0
        self.time = ""
        self.date = ""

def queryDB():
    try:
        connection = mysql.connector.connect(host=os.environ.get('RDS_HOST'),
                                            database=os.environ.get('RDS_DATABASE'),
                                            user=os.environ.get('RDS_USER'),
                                            password=os.environ.get('RDS_PASSWORD'))

        sql_select_Query = "SELECT * FROM logs2 ORDER BY date DESC, time DESC LIMIT 10"
        cursor = connection.cursor()
        cursor.execute(sql_select_Query)
        records = cursor.fetchall()

        out_data = []

        for row in records:
            row_data = LogEntry()
            row_data.date = row[1]
            row_data.time = row[2]
            row_data.cntPerson = row[3]
            row_data.cntDogs = row[4]
            out_data.append(row_data)
        return out_data

    except Error as e:
        print("Error while connecting to MySQL", e)
    finally:
        if (connection.is_connected()):
            cursor.close()
            connection.close()
            print("MySQL connection is closed")
