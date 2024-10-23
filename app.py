from flask import Flask,request
import pickle

with open('model.pkl','rb') as model:
    classifier=pickle.load(model)

app=Flask(__name__)

@app.route('/')
def home():
    return 'API Server Online'

@app.route('/predict',methods=['GET','POST'])
def predict():
    m=float(request.args.get('m'))
    n=float(request.args.get('n'))
    result=classifier.predict([[m,n]])[0]
    if result=="bin is not full":
        return "Bin is not yet full"
    else:
        return "Bin is full.Please clean it"
    
if __name__=="__main__":
    app.run(host="0.0.0.0",port=2000)