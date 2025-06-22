import os
import osmnx as ox
import pandas as pd
import networkx as nx

place_name = "Noida, India"
graph = ox.graph_from_place(place_name, network_type='drive')
graph = ox.project_graph(graph)

nodes, edges = ox.graph_to_gdfs(graph)
edges = edges.reset_index()

# Export nodes
nodes_out = nodes[['x', 'y']].copy()
nodes_out['id'] = nodes_out.index
nodes_out = nodes_out[['id', 'x', 'y']]
nodes_out.to_csv("../data/nodes.csv", index=False)

# Export edges
edges_out = edges[['u', 'v', 'length']].copy()
edges_out.to_csv("../data/edges.csv", index=False)


print("✅ Exported nodes.csv and edges.csv to data/")
