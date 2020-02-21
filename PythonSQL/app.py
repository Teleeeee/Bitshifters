from dotenv import load_dotenv
import os
import pysql_query
from flask import Flask

app = Flask(__name__)

@app.route('/')
def hello():
    outStr = ""
    testData = pysql_query.queryDB()
    for data in testData:
        outStr += "Date: " + str(data.date) + ", Time: " + str(data.time) + ", People: " + str(data.cntPerson)
        outStr += "<br/>"
    return outStr

if __name__ == '__main__':
    load_dotenv()
    app.run()