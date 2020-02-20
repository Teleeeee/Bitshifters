from flask import Flask, request
from flask import render_template, send_from_directory

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

if __name__ == '__main__':
        app.run()


app.run(debug=True )
