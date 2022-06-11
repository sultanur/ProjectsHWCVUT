"""Creating an API from a ML model using Flask:
1.Loading the already persisted model into memory when the app starts
2.Create API endpoint that takes input variables, transform them into the appropriate format and returns predictions

input to the API (JSON list of inputs):
[
    {"age": 24, "sex": "female","embarked":"C", "pclass": 3 },
    {"age": 24, "sex": "male","embarked":"C",  "pclass": 3 },
    {"age": 74, "sex": "female","embarked":"Q", "pclass": 1 },
    {"age": 74, "sex": "male","embarked":"Q", "pclass": 1 },
    {"age": 44, "sex": "female","embarked":"S", "pclass": 2 },
    {"age": 44, "sex": "male","embarked":"S", "pclass": 2 }
]

API will output like the following (survival statuses: 0 is not survived, 1 is survived)
{"prediction": "[1, 0, 1, 0, 0, 0]"}
"""
from flask import Flask, request, jsonify
import joblib
import traceback
import pandas as pd
import sys

app = Flask(__name__)


@app.route('/predict', methods=['POST'])
def predict():
    if lr:
        try:
            json_ = request.json
            print(json_)
            query = pd.get_dummies(pd.DataFrame(json_))
            query = query.reindex(columns=model_columns, fill_value=0)
            prediction = list(lr.predict(query))

            return jsonify({'prediction': str(prediction)})
        except:
            return jsonify({'trace': traceback.format_exc()})
    else:
        print('Train the model first')
        return ('No model here to use')


if __name__ == '__main__':
    try:
        port = int(sys.argv[1])  # for cmd line input
    except:
        port = 12121

    lr = joblib.load('model.pkl')
    print('Model loaded')
    model_columns = joblib.load('model_columns.pkl')
    print('Model columns loaded')

    app.run(port=port, debug=True)
