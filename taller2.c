#include <stdio.h>
#include <stdlib.h> // Necesario para malloc, calloc y free

int main()
{
    int estudiantes;
    int asignaturas = 3;

    printf("Ingrese el numero de estudiantes: ");
    scanf("%d", &estudiantes);

    // Reserva dinámica de memoria (DESPUÉS de saber cuántos estudiantes son)
    float *prom_est = (float *)malloc(estudiantes * sizeof(float));
    float *prom_asig = (float *)malloc(asignaturas * sizeof(float));

    // Declaración y reserva para las variables de estadísticas
    float *max_est = (float *)malloc(estudiantes * sizeof(float));
    float *min_est = (float *)malloc(estudiantes * sizeof(float));
    float *max_asig = (float *)malloc(asignaturas * sizeof(float));
    float *min_asig = (float *)malloc(asignaturas * sizeof(float));
    int *aprob_asig = (int *)calloc(asignaturas, sizeof(int)); // calloc inicia todo en 0

    // Reserva dinámica para la matriz de calificaciones
    float **calif = (float **)malloc(estudiantes * sizeof(float *));
    for (int i = 0; i < estudiantes; i++)
    {
        *(calif + i) = (float *)malloc(asignaturas * sizeof(float));
    }

    // Ingreso de calificaciones
    for (int i = 0; i < estudiantes; i++)
    {
        printf("\nEstudiante %d:\n", i + 1);
        for (int j = 0; j < asignaturas; j++)
        {
            printf("  Asignatura %d: ", j + 1);
            // scanf también puede usar punteros directos
            scanf("%f", *(calif + i) + j);
        }

    }

    // ==================== CÁLCULOS ====================

    // Promedio obtenido por estudiante
    for (int i = 0; i < estudiantes; i++)
    {
        float suma = 0;
        for (int j = 0; j < asignaturas; j++)
        {
            suma += *(*(calif + i) + j);
        }
        *(prom_est + i) = suma / asignaturas;
    }

    // Promedio por asignatura
    for (int j = 0; j < asignaturas; j++)
    {
        float suma = 0;
        for (int i = 0; i < estudiantes; i++)
        {
            suma += *(*(calif + i) + j);
        }
        *(prom_asig + j) = suma / estudiantes;
    }

    // Máx y mín obtenidos por estudiante (Con punteros)
    for (int i = 0; i < estudiantes; i++)
    {
        *(max_est + i) = *(*(calif + i) + 0);
        *(min_est + i) = *(*(calif + i) + 0);
        for (int j = 1; j < asignaturas; j++)
        {
            if (*(*(calif + i) + j) > *(max_est + i))
                *(max_est + i) = *(*(calif + i) + j);
            if (*(*(calif + i) + j) < *(min_est + i))
                *(min_est + i) = *(*(calif + i) + j);
        }
    }

    // Máx y mín por asignatura
    for (int j = 0; j < 3; j++)
    {
        max_asig[j] = min_asig[j] = calif[0][j];
        for (int i = 1; i < 5; i++)
        {
            if (calif[i][j] > max_asig[j])
                max_asig[j] = calif[i][j];
            if (calif[i][j] < min_asig[j])
                min_asig[j] = calif[i][j];
        }
    }

    // Aprobados por asignatura
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            if (calif[i][j] >= 6)
                aprob_asig[j]++;
        }
    }

    // ==================== RESULTADOS OBTENIDOS ====================
    printf("\n=== RESULTADOS ===\n");

    printf("\nPromedio de calificaciones por estudiante:\n");
    for (int i = 0; i < 5; i++)
        printf("  Estudiante %d: %.2f\n", i + 1, prom_est[i]);

    printf("\nPromedio de calificaciones por asignatura:\n");
    for (int j = 0; j < 3; j++)
        printf("  Asignatura %d: %.2f\n", j + 1, prom_asig[j]);

    printf("\nCalificación más alta y baja por estudiante:\n");
    for (int i = 0; i < 5; i++)
        printf("  Estudiante %d → Máx: %.2f  Mín: %.2f\n", i + 1, max_est[i], min_est[i]);

    printf("\nCalificación más alta y baja por asignatura:\n");
    for (int j = 0; j < 3; j++)
        printf("  Asignatura %d → Máx: %.2f  Mín: %.2f\n", j + 1, max_asig[j], min_asig[j]);

    printf("\nNúmero de estudiantes aprobados y reprobados por asignatura:\n");
    for (int j = 0; j < 3; j++)
        printf("  Asignatura %d → Aprobados: %d  Reprobados: %d\n",
               j + 1, aprob_asig[j], 5 - aprob_asig[j]);

    return 0;
}