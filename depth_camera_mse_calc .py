import numpy as np
import os
import pandas as pd

class RawImage():

    def __init__(self, name):

        self.name = name

        if "100" in self.name:
            self.distance = 1000
        else:
            self.distance = int(self.name[:2]) * 10

        self.directory = "C:\\Users\\alatan\\Downloads\\DepthHistogram\\FinalImages"
        self.raw_data = np.fromfile(f"{self.directory}\\{self.name}.raw", dtype=np.uint16)

    def error_calc(self):

        zero_count = 0
        total_diff = 0

        for i in self.raw_data:
                if i != 0:
                    diff = abs(i-self.distance)
                    total_diff += diff
                else:
                    zero_count += 1
                    continue

                error_per_pixel = total_diff/((240 * 424)-zero_count)
                total_error = error_per_pixel / self.distance * 100

        return round(total_error, 2)


num_list = []
name_list = []

for file in os.listdir("C:\\Users\\alatan\\Downloads\\DepthHistogram\\FinalImages"):

    if file[-4:] == ".raw":
        name = file[:-4]
        raw_img = RawImage(name)

        num_list.append(raw_img.error_calc())
        name_list.append(name)

    else:
        continue

data_sheet = pd.Series(num_list, name_list)
print(data_sheet.sort_values(ascending=True))
