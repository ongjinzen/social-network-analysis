/*
 * Graph Visualiser
 * Written By Zain Afzal for cs2521
 *
 * Creates a JSON rep of a graph for use
 * with Sigma.js
 *
 * Written by  zain.afz@gmail.com  
 */
#include "GraphVis.h"
#include "CentralityMeasures.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#define PI 3.14159265

char* nodeTmp = "    {id:'%d',label:'%d',x:%f,y:%f, size:0.2, color: getColor(%f,gradient)}";
char* edgeTmp = "    {source:'%d',target:'%d',id:'%d',label:'%d',type: 'curvedArrow'}";

NodeValues makeBlankNodes(int nV) {
		NodeValues result;
		result.noNodes = nV;
		result.values = calloc(sizeof(double),nV);
		int i = 0;
		for(i=0; i < result.noNodes; i++) {
	    result.values[i] = 1;
	  }
		return result;
}

NodeValues normalise(NodeValues nodes) {
  int i = 0;
  double max = -1;
  for(i=0; i < nodes.noNodes; i++) {
    if(nodes.values[i] > max) max = nodes.values[i];
  }
  for(i=0; i < nodes.noNodes; i++) {
    nodes.values[i] = nodes.values[i]/max;
  }
  return nodes;
}

NodeValues getNodes(Graph g, int mode) {
  if (mode == DEGREE)
    return normalise(degreeCentrality(g));
	if (mode == DEGREE_IN)
	  return normalise(outDegreeCentrality(g));
	if (mode == DEGREE_OUT)
		return normalise(inDegreeCentrality(g));
	if (mode == BETWEENNESS)
		return normalise(betweennessCentrality(g));
	if (mode == CLOSENESS)
		return normalise(closenessCentrality(g));
  return makeBlankNodes(numVerticies(g));
}

void graphVis(Graph g, int mode) {
  FILE *f = fopen("graphVisFiles/data.js","w");
  fprintf(f, "g = {\n  nodes: [\n");
  int i = 0;
  float x = 0;
  float y = 0;
  float a = 0;
  int numVert = numVerticies(g);
  float deltaAngle = 360/numVert;
  float r = 0.3;
  NodeValues nodes = getNodes(g,mode);

  for(i=0; i < numVert; i++) {
    x = r * cos(a*(PI / 180.0));
    y = r * sin(a*(PI / 180.0));
    a += deltaAngle;
    fprintf(f, nodeTmp,i,i,x,y,nodes.values[i]);
    if(i != numVert-1) fprintf(f, ",\n");
  }
  fprintf(f, "\n  ],\n");
  fprintf(f, "  edges: [\n");
  int c = 0;
  for(i=0; i < numVert; i++) {
    AdjList org = outIncident(g,i);
    AdjList l = outIncident(g,i);
    while(l != NULL) {
      fprintf(f,edgeTmp,i,l->w,c,l->weight);
      c++;
      l = l->next;
      if(l != NULL) fprintf(f, ",\n");
    }
    if (i != numVert-1 && org != NULL) fprintf(f, ",\n");
  }
  fprintf(f, "\n  ]\n}");
  char cwd[1024];
  char * res = getcwd(cwd, 1024);
	free(nodes.values);
	fclose(f);
  printf("See Graph: file://%s/graphVisFiles/seeGraph.html\n",res);
}
