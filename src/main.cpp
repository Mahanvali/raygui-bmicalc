#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui.h"
#include "math.h"

const int screenWidth = 300;
const int screenHeight = 300;

bool isAgeActive = false;
bool isWeightActive = false;
bool isHeightActive = false;

char AgeValue[8] = "\0";
char WeightValue[8] = "\0";
char HeightValue[8] = "\0";
char BMIValue[8] = "\0";

float age, weight, height, bmi;

Rectangle ageRec = {10, 10, 100, 30};
Rectangle weightRec = {10, 50, 100, 30};
Rectangle heightRec = {10, 90, 100, 30};
Rectangle calculateRec = {10, 130, 100, 30};
Rectangle BMIRec = {10, 170, 100, 30};

void Update();
void CalculateBMI(float weight, float height, float& bmi);

int main(){
    InitWindow(screenWidth, screenHeight, "BMI CALCULATOR");
    while(!WindowShouldClose()){
        Update();
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("AGE (YRS)", 120, 20, 15, RED);
            DrawText("MASS (KGS)", 120, 60, 15, RED);
            DrawText("HEIGHT (CM)", 120, 100, 15, RED);
            DrawText("BMI", 120, 180, 15, RED);
        EndDrawing();
    }
    return 0;
    CloseWindow();
}

void Update(){
    //  Convert char to float
    age = atof(AgeValue);
    weight = atof(WeightValue);
    height = atof(HeightValue);
    
    //  Check the collision between the mouse and each rectangle for input
    if(CheckCollisionPointRec(GetMousePosition(), ageRec)){
        isWeightActive = false;
        isHeightActive = false;
        isAgeActive = true;
    }else if(CheckCollisionPointRec(GetMousePosition(), weightRec)){
        isAgeActive = false;
        isHeightActive = false;
        isWeightActive = true;
    }else if(CheckCollisionPointRec(GetMousePosition(), heightRec)){
        isAgeActive = false;
        isWeightActive = false;
        isHeightActive = true;
    }
    //  Create the text boxes
    GuiTextBox(ageRec, AgeValue, 8, isAgeActive);
    GuiTextBox(weightRec, WeightValue, 8, isWeightActive);
    GuiTextBox(heightRec, HeightValue, 8, isHeightActive);
    GuiTextBox(BMIRec, BMIValue, 8, false);

    if(CheckCollisionPointRec(GetMousePosition(), calculateRec)){
        isAgeActive = false;
        isWeightActive = false;
        isHeightActive = false;
    }
    //  Calculate Button
    if(GuiButton(calculateRec, "Calculate")){
        CalculateBMI(weight, height, bmi);

        sprintf(BMIValue, "%f", bmi);
    }

}
//  BMI Calculation function
void CalculateBMI(float weight, float height, float &bmi)
{
    bmi = weight/pow(height, 2);
}
