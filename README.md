## crypt  


![screenshot.png](https://github.com/aussie114/crypt/blob/master/data/screenshot.png)  


## About  


This is a password generator and acts as a password manager by generating the same output when provided with the same input.


The program is not cryptographically safe and the randomization is dependent on your input.  

## Usage  


You can either generate a password in a service username length and special at runtime or file and then entering a keyword  


If you wish to generate from file you must pass in a csv file at execution (e.g. ./crypt data/example.csv) The format of the CSV file must be as follows:  
service, username, length, special(true or false)  
service, username, length, special(true or false)  
service, username, length, special(true or false)  
...  

Check the example.csv in the data folder.  

There is also a copy of this program written in python in the bin folder.
