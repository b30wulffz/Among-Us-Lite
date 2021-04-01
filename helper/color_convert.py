red = [192, 21, 2]
dark_red = [120, 11, 57]

grey = [149, 199, 222]
dark_grey = [74, 100, 108]

cyan = [88, 253, 216]
dark_cyan = [59, 167, 193]

blue = [34, 37, 221]
dark_blue = [18, 11, 147]

orange = [245, 176, 65]
yellow = [241, 196, 15]

sky_blue = [202, 247, 227]
dark_sky_blue = [180, 244, 215]

msg_red = [199, 0, 57]
msg_green = [192, 226, 24]
msg_orange = [226, 159, 24]
col = [29, 131, 72]
col = [ 25, 111, 61]

color = col
for c in color:
    k = round(c/255, 5)
    print("{}f, ".format(k), end="")