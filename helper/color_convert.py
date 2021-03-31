red = [192, 21, 2]
dark_red = [120, 11, 57]

grey = [149, 199, 222]
dark_grey = [74, 100, 108]

cyan = [88, 253, 216]
dark_cyan = [59, 167, 193]

blue = [34, 37, 221]
dark_blue = [18, 11, 147]

color = dark_blue
for c in color:
    k = round(c/255, 5)
    print("{}f, ".format(k), end="")