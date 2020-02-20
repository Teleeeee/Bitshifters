from flask import Flask, request
from flask import render_template, send_from_directory
from dotenv import load_dotenv
import os
import pysql_query
import json

app = Flask(__name__)

@app.route('/team.html')
def team_page():
	return render_template('team.html')

@app.route('/')
@app.route('/index.html')
def index_page():
	return render_template('index.html')

@app.route('/about.html')
def about_page():
	return render_template('about.html')

@app.route('/service')
def service():
	testData = pysql_query.queryDB()
	return {
		"time": str(testData[0].time),
		"peopleCount": str(testData[0].cntPerson)
	}

if __name__ == '__main__':
	load_dotenv()
	app.run()


app.run(debug=True )
