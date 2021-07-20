#include "Graphlib.h"

int main(){
    FILE* source;
    source = fopen("dothi.txt", "r");
    if (source == NULL){
        printf("Error!\n");
        exit(1);
    }
    Graph graph = createGraph();
    int choice;
    int flag = 0;
    do{
        printf("=====================================\n");
        printf("1. In ra danh sach ID\n");
        printf("2. Tim kiem ban than\n");
        printf("3. Kiem tra quan he bac cau\n");
        printf("4. Kiem tra ban chung\n");
        printf("5. Thoat\n");
        printf("=====================================\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        if (choice <= 0 || choice >= 6) printf("Nhap khong hop le!\n");
        else if (choice >=1 && choice <=5){
            switch(choice){
                case 1:
                    if (flag == 0){
                        flag = 1;
                        int v, e, id;
                        fscanf(source, "%d %d", &v, &e);
                        for (int i = 0; i < v; i++){
                            char name[10];
                            fscanf(source, "%d %s\n", &id, name);
                            addVertex(graph, id, strdup(name));
                        }
                        int v1, v2; 
                        float w;
                        for (int i = 0; i < e; i++){
                            fscanf(source, "%d %d %f", &v1, &v2, &w);
                            addEdge2(graph, v1, v2, w);
                        }
                        printf("DANH SACH ID: \n");
                        JRB trav;
                        jrb_traverse(trav, graph.vertices){
                            printf("%d\t%s\n", jval_i(trav->key), getVertex(graph, jval_i(trav->key)));
                        }
                    }
                    else printf("Ban da nap do thi!\n");
                    break;
                case 2:
                    if(flag){
                        int id; 
                        printf("Nhap ID: ");
                        scanf("%d", &id);
                        JRB check = jrb_find_int(graph.edges, id);
                        if (check == NULL) printf("%s khong co ban!\n", getVertex(graph, id));
                        else{
                            int output[10];
                            int n = outdegree(graph, id, output);
                            float max = getEdgeValue(graph, id, output[0]);
                            for (int i = 0; i < n; i++){
                                if (getEdgeValue(graph, id, output[i]) > max) max = getEdgeValue(graph, id, output[i]);
                            }
                            printf("%.2f\n", max);
                            for (int i = 0; i < n; i++){
                                if (getEdgeValue(graph, id, output[i]) == max) 
                                    printf("%d %s\n", output[i], getVertex(graph, output[i]));
                            }
                        }
                    }
                    else printf("Ban chua nap do thi!\n");
                    break;
                case 3:
                    if (flag){
                        int v1, v2;
                        printf("Nhap 2 ID: ");
                        scanf("%d %d", &v1, &v2);
                        if (hasEdge(graph, v1, v2) == 1) printf("%s va %s khong co quan he bac cau\n", getVertex(graph, v1), getVertex(graph, v2));
                        else{
                            if (connect(graph, v1, v2) == 1) printf("%s va %s co quan he bac cau\n", getVertex(graph, v1), getVertex(graph, v2));
                            else printf("%s va %s khong co quan he bac cau\n", getVertex(graph, v1), getVertex(graph, v2));
                        }
                    }
                    else printf("Ban chua nap do thi!\n");
                    break;
                case 4:
                    if (flag){
                        int v1, v2, find = 0, out[20];
                        printf("Nhap 2 ID: ");
                        scanf("%d %d", &v1, &v2);
                        int out1[10], out2[10], n1, n2;
                        n1 = outdegree(graph, v1, out1);
                        n2 = outdegree(graph, v2, out2);
                        for (int i = 0; i < n1; i++){
                            for (int j = 0; j < n2; j++){
                                if (out1[i] != v2 && out1[i] == out2[j]) out[find++] = out1[i];
                            }
                        }
                        if (find == 0) printf("%s va %s khong co ban chung!\n", getVertex(graph, v1), getVertex(graph, v2));
                        else{
                            printf("%s va %s co %d ban chung: \n", getVertex(graph, v1), getVertex(graph, v2), find);
                            for (int i = 0; i < find; i++){
                                printf("%d %s\n", out[i], getVertex(graph, out[i]));
                            }
                        }
                    }
                    else printf("Ban chua nap do thi!\n");
                    break;
                case 5: printf("Ban da thoat chuong trinh!\n");
                    break;
            }
        }
    }while(choice != 5);
    fclose(source);
    return 1;
}