#!/usr/bin/env python3

import csv
import requests

CSV_URL = 'https://www.iana.org/assignments/tls-extensiontype-values/tls-extensiontype-values-1.csv'


with open('tls-extensiontype-values-1.csv', newline='') as csvfile:
    rows = list(csv.reader(csvfile, delimiter=','))[1:]
    enum = []
    recommended = []
    for row in rows:
        name = row[1]
        if not ('Reserved' in name or 'Unassigned' in name):
            if 'deprecated' in name:
                name = row[1].split(' ')[0] + "_deprecated"
            if ' ' in name:
                name = row[1].split(' ')[0]

            enum.append(f'{name} = {row[0]}')

            if row[4] == 'Y':
                recommended.append(name)

    

    recommended = list(map(lambda name: 'ExtensionType::' + name, recommended))

    print(',\n'.join(enum))
    print()

    print(',\n'.join(recommended))
