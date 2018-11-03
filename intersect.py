import street

class Point(object):
    def __init__ (self, x, y):
        self.x = float(x)
        self.y = float(y)
    def __str__ (self):
        return '(' + str(self.x) + ',' + str(self.y) + ')'

class Line(object):
    def __init__ (self, src, dst):
        self.src = src
        self.dst = dst

    def __str__(self):
        return str(self.src) + '-->' + str(self.dst)
#method that checks if c lies between a and b
def findInBetween(ax,ay,bx,by,cx,cy):
    #dotproduct is positive and less than square of the distance between a and b
    dotproduct = (cx - ax) * (bx - ax) + (cy - ay)*(by - ay)
    if dotproduct < 0:
        return False
    squaredlengthba = (bx - ax)*(bx - ax) + (by - ay)*(by - ay)
    if dotproduct > squaredlengthba:
        return False
    return True

def intersect (l1, l2):

    x1, y1 = l1.src.x, l1.src.y
    x2, y2 = l1.dst.x, l1.dst.y
    x3, y3 = l2.src.x, l2.src.y
    x4, y4 = l2.dst.x, l2.dst.y

    xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4))
    xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4))
    coincident = False
    if xden == 0:
        xcoor = 0
        #check for coincident streets
        coincident = False
        street_method = street.Street()
        inBetween = street_method.isVertexInBetween((x1,y1),(x2,y2),(x3,y3))
        if inBetween:
            coincident = street_method.isVertexInBetween((x1,y1),(x2,y2),(x4,y4))
        else:
            inBetween = street_method.isVertexInBetween((x3,y3),(x4,y4),(x1,y1))
            if inBetween:
                coincident = street_method.isVertexInBetween((x3,y3),(x4,y4),(x2,y2))
    else:
        xcoor =  xnum / xden

    ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)
    yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)
    if yden == 0:
        ycoor = 0
    else:
        ycoor = ynum / yden

    check_x2 = False
    check_y2 = False
    edges_list = []
    if not coincident:
        if x1 > x2 :
            check_x1 = (x2 <= xcoor <= x1)
        else :
            check_x1 = (x1 <= xcoor <= x2)

        if check_x1 :
            if x3 > x4 :
                check_x2 = (x4 <= xcoor <= x3)
            else :
                check_x2 = (x3 <= xcoor <= x4)

        if y1 > y2 :
            check_y1 = (y2 <= ycoor <= y1)
        else :
            check_y1 = (y1 <= ycoor <= y2)

        if check_y1 :
            if y3 > y4 :
                check_y2 = (y4 <= ycoor <= y3)
            else :
                check_y2 = (y3 <= ycoor <= y4)

        if check_x2 and check_y2:
            if xcoor == -0:
                xcoor = 0
            if ycoor == -0:
                ycoor = 0
            xcoor = float("{:.2f}".format(xcoor))
            ycoor = float("{:.2f}".format(ycoor))
            list_coord = [(x1,y1),(x2,y2),(x3,y3),(x4,y4), (xcoor,ycoor)]

            edges_list.append([(xcoor,ycoor),(x1,y1)])
            edges_list.append([(xcoor,ycoor),(x2,y2)])
            edges_list.append([(xcoor,ycoor),(x3,y3)])
            edges_list.append([(xcoor,ycoor),(x4,y4)])
            return list_coord , edges_list , [(xcoor,ycoor),l1,l2]
        else :
            return -1
    else:
        list_coord = [(x1,y1),(x2,y2),(x3,y3),(x4,y4)]
        if (x1,y1) != (x3,y3):
            edges_list.append([(x1,y1),(x3,y3)])
        if (x2,y2) != (x4,y4):
            edges_list.append([(x2,y2),(x4,y4)])
        if (x1,y1) != (x2,y2):
            edges_list.append([(x1,y1),(x2,y2)])
        if (x3,y3) != (x4,y4):
            edges_list.append([(x3,y3),(x4,y4)])

        return list_coord , edges_list
