from flask import Flask, request, render_template

app = Flask(__name__)

@app.route('/')
def my_form():
    return render_template('index.html')

text = ""
@app.route('/test', methods=['GET', 'POST'])
def my_form_post():
    global text
    if request.method == 'POST':
        text = request.form['text']
        return render_template('index.html', text=text)
    elif request.method == 'GET':
        return text

if __name__ == '__main__':
    app.run(debug=False)