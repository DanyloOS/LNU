#!/usr/bin/env python
# coding: utf-8

# In[1]:

import pandas as pd

url = "https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data"
# load dataset into Pandas DataFrame
df = pd.read_csv(url, names=['sepal length', 'sepal width', 'petal length', 'petal width', 'target'])
df.head()

import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, MinMaxScaler, QuantileTransformer, Normalizer, OrdinalEncoder

# In[2]:


df = pd.read_table('fruit_data_with_colors.txt')
df.head()

# In[3]:


lookup_fruit_name = dict(zip(df.fruit_label.unique(), df.fruit_name.unique()))

X = df[['height', 'width', 'mass', 'color_score']]
y = df['fruit_label']
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)

# # StandardScaler

# In[4]:


fit_transform_data = StandardScaler().fit_transform(X_train)
fit_transform_data[:5]

# # Scaling features to a range

# In[5]:


fit_transform_data = MinMaxScaler().fit_transform(X_train)
fit_transform_data[:5]

# # Mapping to a Uniform distribution

# In[6]:


fit_transform_data = QuantileTransformer(random_state=0).fit_transform(X_train)
fit_transform_data[:5]

# # Normalization

# In[7]:


fit_transform_data = Normalizer().fit_transform(X_train)
fit_transform_data[:5]

# # Encoding categorical features

# In[8]:


enc = OrdinalEncoder()
X = [['male', 'from US', 'uses Safari'], ['female', 'from Europe', 'uses Firefox']]
enc.fit(X)
enc.transform([['female', 'from US', 'uses Safari']])

# # Imputation of missing values

# In[9]:


from sklearn.impute import SimpleImputer

imp = SimpleImputer(missing_values=np.nan, strategy='mean')
imp.fit([[1, 2], [np.nan, 3], [7, 6]])

# In[10]:


X = [[np.nan, 2], [6, np.nan], [7, 6]]
imp.transform(X)

# In[ ]:
