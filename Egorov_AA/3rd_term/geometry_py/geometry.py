from shapely.geometry import Polygon, LineString

from shapely.ops import split


polygon_coords = [(0, 0), (6, 0), (6, 6), (3, 3), (0, 6)]

line_coords = [(0, 4), (6, 4)]


polygon = Polygon(polygon_coords)

line = LineString(line_coords)


result = split(polygon, line)



if not result.is_empty:

    for geom in result.geoms:  
        print(list(geom.exterior.coords))
        
else:

    print("Result is empty")
