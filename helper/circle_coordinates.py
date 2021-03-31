import math

origin = [0.5, 0.0, 0.0]
x = 0.0
radius = origin[0]-x
step = 0.01

vertices = []
color= "0.75294f, 0.08235f, 0.00784f," # red
color = "0.13333f, 0.1451f, 0.86667f," # blue # imposter

while x<=1.0:
    y = math.sqrt( radius**2 - (x-origin[0])**2 ) + origin[1]
    y = round(y, 6)
    print(x, y)
    x += step
    x = round(x, 2)
    vertices.append([x, y, 0.0])

print("Vertices")
print()

for i in range(0, len(vertices) - 1):
    # print("{}f, {}f, {}f, ".format(vertices[i][1], vertices[i][0], vertices[i][2]))
    # print("{}f, {}f, {}f, ".format(origin[1], origin[0], origin[2]))
    # print("{}f, {}f, {}f, ".format(vertices[i+1][1], vertices[i+1][0], vertices[i+1][2]))
    # print()

    print("[{}, {}, {}], ".format(vertices[i][1], vertices[i][0], vertices[i][2]))
    print("[{}, {}, {}], ".format(origin[1], origin[0], origin[2]))
    print("[{}, {}, {}], ".format(vertices[i+1][1], vertices[i+1][0], vertices[i+1][2]))
    print()

def square_print(coord):
    # print("{}f, {}f, {}f, ".format(-coord[0][1], coord[0][0], coord[0][2]))
    # print("{}f, {}f, {}f, ".format(-coord[1][1], coord[1][0], coord[1][2]))
    # print("{}f, {}f, {}f, ".format(-coord[2][1], coord[2][0], coord[2][2]))
    # print()
    # print("{}f, {}f, {}f, ".format(-coord[2][1], coord[2][0], coord[2][2]))
    # print("{}f, {}f, {}f, ".format(-coord[3][1], coord[3][0], coord[3][2]))
    # print("{}f, {}f, {}f, ".format(-coord[0][1], coord[0][0], coord[0][2]))
    # print()

    print("[{}, {}, {}], ".format(-coord[0][1], coord[0][0], coord[0][2]))
    print("[{}, {}, {}], ".format(-coord[1][1], coord[1][0], coord[1][2]))
    print("[{}, {}, {}], ".format(-coord[2][1], coord[2][0], coord[2][2]))
    print()
    print("[{}, {}, {}], ".format(-coord[3][1], coord[3][0], coord[3][2]))
    print("[{}, {}, {}], ".format(-coord[2][1], coord[2][0], coord[2][2]))
    print("[{}, {}, {}], ".format(-coord[0][1], coord[0][0], coord[0][2]))
    print()

triangle_cnt = len(vertices) - 1

# body
body = [[0.0,0.0,0.0], [0.0,2.0,0.0], [1.0,2.0,0.0], [1.0,0.0,0.0]]
square_print(body)
triangle_cnt+=2

#lens
lens = [[0.4, 0.3, 0.0], [0.4, 0.9, 0.0], [1.0, 0.9, 0.0], [1.0, 0.3, 0.0]]
square_print(lens)
triangle_cnt+=2

#left leg
left_leg = [[0.0,2.0,0.0], [0.0, 2.4, 0.0], [0.4, 2.4, 0.0], [0.4, 2.0, 0.0]]
square_print(left_leg)
triangle_cnt+=2

#right leg
right_leg = [[0.6,2.0,0.0], [0.6, 2.4, 0.0], [1.0, 2.4, 0.0], [1.0, 2.0, 0.0]]
square_print(right_leg)
triangle_cnt+=2

#oxygen tank
oxygen_tank = [[-0.3, 0.6, 0.0], [-0.3, 1.8, 0.0], [0.0, 1.8, 0.0], [0.0, 0.6, 0.0]]
square_print(oxygen_tank)
triangle_cnt+=2

print("Colors")
print()

for i in range(0, len(vertices) - 1):
    print(color)
    print(color)
    print(color)
    print()


def square_color_print(col, col2=None):
    print(col)
    print(col)
    print(col)
    print()
    if(col2 is not None):    
        print(col2)
        print(col2)
        print(col2)
        print()
    else:
        print(col)
        print(col)
        print(col)
        print()

# body
body_col = "0.75294f, 0.08235f, 0.00784f,"  # red
body_col = "0.13333f, 0.1451f, 0.86667f," # blue # imposter

square_color_print(body_col)

# lens
lens_col1 = "0.2902f, 0.39216f, 0.42353f," # dark grey
lens_col2 = "0.58431f, 0.78039f, 0.87059f," # grey
square_color_print(lens_col1, lens_col2)

# left leg
left_leg_col = "0.47059f, 0.04314f, 0.22353f," #dark red
left_leg_col = "0.07059f, 0.04314f, 0.57647f," #dark blue #imposter
square_color_print(left_leg_col)

# right lef
right_leg_col = "0.47059f, 0.04314f, 0.22353f," #dark red
right_leg_col = "0.07059f, 0.04314f, 0.57647f," #dark blue #imposter
square_color_print(right_leg_col)

# oxygen tank
oxygen_tank_col = "0.47059f, 0.04314f, 0.22353f," #dark red
oxygen_tank_col = "0.07059f, 0.04314f, 0.57647f," #dark blue #imposter
square_color_print(oxygen_tank_col)

print("Triangles: {}".format(triangle_cnt))