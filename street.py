import intersect
import math
import sys

class Street:
    street_dict = {}
    vertices_dict = {}

    def addStreet(self,street_name, coordinates, command):
        if command == 'a':
            if street_name in self.street_dict:
                sys.stderr.write("Error : street already exists\n")
            else :
                self.street_dict[street_name] = coordinates
        else :
            self.street_dict[street_name] = coordinates

    def removeStreet(self,street_name):
        if street_name in self.street_dict:
            if(self.street_dict[street_name]):
                del self.street_dict[street_name]
                return "SUCCESS"
        else:
            sys.stderr.write("Error : 'c' or 'r' specified for a street that does not exist\n")

    def getCoordinates(self, input_string):
        input_string = input_string.strip()

        if not input_string.endswith(")"):
            return False
        start_coord = input_string.find("(")
        input_string = input_string[start_coord+1:len(input_string)]
        input_string = input_string.replace(" ","")
        input_string = input_string.replace("(",",")
        input_string = input_string.replace(")","")
        final_coord_list = []
        coord_list = input_string.split(",")
        #print coord_list
        for coord in coord_list:
            try :
                float(coord)
            except ValueError:
                return False

        if len(coord_list)%2 != 0:
            return False
        else:
            for x in range(0, len(coord_list),2):
                final_coord_list.append((coord_list[x],coord_list[x+1]))
            return final_coord_list

    def getVerticesOutput(self,final_intersects):
        #remove duplicates
        vertices = list(set(final_intersects))
        vertices_local_dict = {}
        if not bool(self.vertices_dict):

            i = 0
            for value in vertices:
                self.vertices_dict[i] = value
                i = i+1
        else:
            for key in self.vertices_dict:
                if self.vertices_dict[key] in vertices:
                    vertices_local_dict[key] = self.vertices_dict[key]
                j = key+1

            for value in vertices:
                if value not in self.vertices_dict.values():
                    vertices_local_dict[j] = value
                    j = j+1

            self.vertices_dict.clear()
            self.vertices_dict.update(vertices_local_dict)

        sys.stdout.write("V "+str(len(self.vertices_dict))+"\n");
        sys.stdout.write("V = {\n")
        for key in self.vertices_dict:
            sys.stdout.write(" {}: {}\n".format(key,self.vertices_dict[key]))
            #vertice_string = vertice_string + str(key) + ":" + str(self.vertices_dict[key]) +"\n"
        sys.stdout.write("}")

    def isVertexInBetween(self,point1,point2,current):
        dxc = current[0] - point1[0]
        dyc = current[1] - point1[1]

        dxl = point2[0] - point1[0]
        dyl = point2[1] - point1[1]

        cross = round(dxc * dyl) - round(dyc * dxl)
        if cross != 0:
            return False #current does not lie on the line between point1 and point2

        if abs(dxl) >= abs(dyl):
            if dxl > 0 :
                return point1[0] <= current[0] and current[0] <= point2[0]
            else :
                return point2[0] <= current[0] and current[0] <= point1[0]
        else:
            if dyl > 0 :
                return point1[1] <= current[1] and current[1] <= point2[1]
            else:
                return point2[1] <= current[1] and current[1] <= point1[1]

    def getEdgesOutput(self,edge_list, intersection_points, allVertices):

        # logic to get edges between intersetion points and check there is not intesection point betweeen 2 intersection points
        intersection_edges = []

        for i in range(0,len(intersection_points)):
            for j in range(i+1,len(intersection_points)):
                if ((intersection_points[i][1] in intersection_points[j]) or (intersection_points[i][2] in intersection_points[j])) and intersection_points[i][0] != intersection_points[j][0]:
                    pair1 = [intersection_points[i][0],intersection_points[j][0]]
                    pair2 = [intersection_points[j][0],intersection_points[i][0]]
                    if pair1 not in intersection_edges and pair2 not in intersection_edges:
                        intersection_edges.append([intersection_points[i][0],intersection_points[j][0]])

        #print "intersetion points edges",intersection_edges
        edge_list = edge_list + intersection_edges

        final_edges = []
        for values in edge_list:
            isBetween = False
            for vertex in allVertices:
                if vertex != values[0] and vertex != values[1]:
                     #print "values--->",values[0] , values[1]
                     #print "vertex-->",vertex

                     isBetween = self.isVertexInBetween(values[0],values[1],vertex)
                     #print "in between -->",isBetween
                     if isBetween:
                         '''if vertex in intersections:
                             p1 = [values[0],vertex]
                             p2 = [vertex,values[0]]
                             p3 = [values[1],vertex]
                             p4 = [vertex,values[1]]
                             if p1 not in final_edges and p2 not in final_edges:
                                 final_edges.append(p2)
                             if p3 not in final_edges and p4 not in final_edges:
                                 final_edges.append(p4)'''
                         break
            if not isBetween:
                if values not in final_edges:
                    final_edges.append(values)

        edges_set = set()
        for edges in final_edges:
            edge = ""
            for key in self.vertices_dict:
                if self.vertices_dict[key] == edges[0]:
                    edge = "<"+ str(key)
            for key in self.vertices_dict:
                if self.vertices_dict[key] == edges[1]:
                    edge = edge+","+ str(key)+">"
            edges_set.add(edge)
        y = ",".join(edges_set)
        sys.stdout.write("E {"+y+"}")
        #if y != "":
        #    sys.stdout.write("E {"+ y+"}")
        #else:
            #sys.stdout.write("\nE = {\n"+y+"}\n")

    def generateGraph(self):
        points_dict = {}
        #print 'street dict  ---------------------',self.street_dict
        for key in self.street_dict:
            i = 0
            point_list = []
            while i < len(self.street_dict[key]):
                point = intersect.Point(self.street_dict[key][i][0],self.street_dict[key][i][1])
                i += 1
                point_list.append(point)
            points_dict[key] = point_list

        lines_dict = {}
        complete_lines = []
        for key in points_dict:
            i = 0
            line_list = []
            while i < len(points_dict[key])-1:
                #print points_dict[key][i]
                #print points_dict[key][i+1]
                line = intersect.Line(points_dict[key][i], points_dict[key][i+1])
                #print line
                #line = intersect.Line(self.street_dict[key][0],self.street_dict[key][1])
                i += 1
                line_list.append(line)
            lines_dict[key] = line_list
            complete_lines.append(line_list)

        #find intersect
        final_intersects = []
        final_edges = []
        intersection_points = []
        #print "length :"+str(len(complete_lines))
        for i in range(0, len(complete_lines)):
            for k in range (i+1, len(complete_lines)):
                for j in range(0,len(complete_lines[i])):
                    for m in range(0, len(complete_lines[k])):
                        #print "before function call"
                        point = intersect.intersect(complete_lines[i][j],complete_lines[k][m])
                        if(point != -1):
                            final_intersects = final_intersects + point[0]
                            final_edges = final_edges + point[1]
                            if len(point) == 3:
                                intersection_points.append(point[2])
        #print final_intersects

        intersections = []
        for i in intersection_points:
            intersections.append(i[0])
        #
        #print final_edges

        #print "intersections ::",intersections
        new_edges = []
        for edge in final_edges:
            for vertex in intersections:
                isBetween = self.isVertexInBetween(edge[0],edge[1],vertex)
                if isBetween and edge[0] != vertex and edge[1] != vertex:
                    new_edge1 = [edge[0],vertex]
                    new_edge2 = [edge[1],vertex]
                    new_edges.append(new_edge1)
                    new_edges.append(new_edge2)

        #print "new edges   ",new_edges
        final_edges = final_edges + new_edges

        edges_remove_dup = []
        #edges_remove_dup.extend(final_edges)
        #print "edges_remove_dup before-------->",edges_remove_dup
        for a in final_edges:
            l = [a[1],a[0]]
            if a not in edges_remove_dup and l not in edges_remove_dup and l != a:
                edges_remove_dup.append(a)
        #print "edges_remove_dup after-------->",edges_remove_dup
        b_set = set((map(tuple,edges_remove_dup)))  #need to convert the inner lists to tuples so they are hashable
        b = map(list,b_set)
        #print "intersection points :::::",intersection_points

        #return final_intersects
        self.getVerticesOutput(final_intersects)
        self.getEdgesOutput(b,intersection_points,  list(set(final_intersects)))
