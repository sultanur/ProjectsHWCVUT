
import pandas as pd
import numpy as np
import joblib
from sklearn.tree import DecisionTreeClassifier

#reading data from csv file
df = pd.read_csv("data.csv")

#creating table with five columns
include = ["age", "sex", "embarked", "pclass", "survived"]
data = df[include]

#start of data reprocessing: if column with non-numeric value -> append in a list categoricals, /
# if column is numerical then check for missing values (if true then fill with 0)
categorical = []
for col, col_type in data.dtypes.iteritems():
    if col_type == 'O':
        categorical.append(col)
    else:
        data[col].fillna(0, inplace=True)

data_OHE = pd.get_dummies(data, columns=categorical, dummy_na=True)

#using LogisticRegression for training ML model
dependent_var = 'survived'
x_data = data_OHE[data_OHE.columns.difference([dependent_var])]
y_data = data_OHE[dependent_var]
lr = DecisionTreeClassifier()
lr.fit(x_data, y_data)

#Serialization of built ML model(Pickling), for this use joblib. After it Pegression model will be persisted
joblib.dump(lr, 'model.pkl')
print("Model is serialized!")
#loading model
lr = joblib.load('model.pkl')

# in case if input doesn't have data for all columns we need to  persist the list of  columns during model training
model_columns = list(x_data.columns)
joblib.dump(model_columns, 'model_columns.pkl')
print("Models columns also persisted")

