#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include<algorithm>
#include<sstream>
#include <regex>

int main()
{
    string row_data;
    vector <string> row;
    int flag = 1;
    int counter = 1;
    //Sorting component files separately
    int nfile = 16;
    do
    {
        string file_name = to_string(counter) + "-Books_rating.csv";
        string location = "D:/Sorting Big File/" + file_name;
        ifstream csv_file(location, ios_base::binary);

        if (!csv_file.is_open())
        {
            cout << "File Not Open" << '\n';
            flag = 0;
        }
        while (csv_file.peek() != EOF)
        {
            getline(csv_file, row_data, '\n');
            row.push_back(row_data);
        }
        sort(row.begin(), row.end());
        string name = "sorted " + file_name;
        ofstream sorted_file(name);
        for (size_t i = 0; i < row.size(); i++)
        {
            sorted_file << row[i] << '\n';
        }
        counter++;
        row.clear();
        csv_file.close();
    } while (flag == 1);

    //Combining sorted component files to create the final file by using merge sort algorithm
    ofstream finalfile("sorted_books_rating.csv");

    int done = 0, index = 0;
    string queue[16], fname, temp;
    fstream* filelist = new fstream[nfile];
    for (int i = 0; i < nfile; i++) 
    {
        fname = "sorted " + to_string(i + 1) + "-Books_rating.csv";
        filelist[i].open(fname, ios_base::in | ios_base::binary);
    }

    for (int i = 0; i < nfile; i++)
    {
        queue[i] = "added";
    }

    while (done < nfile)
    {
        for (int i = 0; i < nfile; i++)
        {
            if (queue[i] == "added")
            {
                if (!filelist[i].eof())
                {
                    getline(filelist[i], temp);
                    queue[i] = temp;
                }
            }
        }

        for (int i = 0; i < nfile; i++)
        {
            if (queue[i] != "added")
            {
                temp = queue[i];
                break;
            }
        }

        for (int i = 0; i < nfile; i++) //find the find needed to add
        {
            if (queue[i] <= temp and queue[i] != "added")
            {
                temp = queue[i];
                index = i;
            }
        }

        if (queue[index] != "added")
        {
            finalfile << queue[index];
        }
        queue[index] = "added";

        done = 0;
        for (int i = 0; i < nfile; i++)
        {
            if (filelist[i].peek() == EOF)
            {
                done++;
            }
        }
    }
    return 0;
}

