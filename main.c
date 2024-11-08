#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FAILED NULL
#define MAX_SIZE 100
#define MAP_SIZE 8
//Imported boolean

/*
 * Progress Log:
 * What is troubling me? I need to know how to check non-terminals
 * Actually, I can skip that. I need to get a string first.
 * 3:09 pm: I got a string! \0 marks its end. Need a match() and a lookahead()
 */

char* nextInputChar; //This is a char array. You can traverse it through int!

//IMPORTED TREE CONTENT FROM INSTRUCTOR
typedef struct NODE *TREE;

struct NODE {
    char label;
    TREE leftmostChild, rightSibling;
};

TREE makeNode0(char x)
{
    TREE root;
    root = (TREE) malloc(sizeof(struct NODE));
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}

TREE makeNode1(char x, TREE t)
{
    TREE root;
    root = makeNode0(x);
    root->leftmostChild = t;
    return root;
}

TREE makeNode2(char x, TREE t1, TREE t2) //ADDED BY ME
{
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    return root;
}

TREE makeNode3(char x, TREE t1, TREE t2, TREE t3) //ADDED BY ME
{
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    return root;
}

TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4)
{
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    t3->rightSibling = t4;
    return root;
}

TREE B(void);
TREE ST(void); //ST == D
TREE S(void);
TREE F(void);
TREE TT(void); //TT == Y
TREE T(void);
TREE ET(void); //ET == R
TREE E(void);
//IMPORTED TREE CONTENT FROM INSTRUCTOR

//MY CODE FOR TRAVERSING LMCRS TREE
void traverseLRCRS(struct NODE *root, int depth) {
    if (root == NULL) {
        return;
    }

    // Print the current node's data, indented according to depth
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%c\n", root->label);

    // Traverse the leftmost child, indented one level deeper
    if (root->leftmostChild != NULL) {
        traverseLRCRS(root->leftmostChild, depth + 1);
    }

    // Traverse the right sibling at the same level of indentation
    if (root->rightSibling != NULL) {
        traverseLRCRS(root->rightSibling, depth);
    }
}
//MY CODE FOR TRAVERSING LMCRS TREE

void printArray(char* input_array){
    int i = 0;
    while(input_array[i] != '\0'){
        printf("%c", input_array[i]);
        i = i + 1;
    }
    i = i + 1;
    printf("%c", input_array[i]);
}

char* inputGetter(void){ //Modified from my project 1.
    int processed_input_len;
    char input_line[256];
    fgets(input_line, 256, stdin);

    for (int i = 0; i < 256; i++) {
        if (input_line[i] == '\n') { //'\n' is the effective stopper.
            break;
        }
        processed_input_len = i;
    }

    processed_input_len = processed_input_len + 2;
    //Filling up the processed_input[]
    char* processed_input = malloc(processed_input_len);

    for (int i = 0; i < 256; i++) {
        processed_input[i] = input_line[i];
        if (processed_input[i] == '\n') {
            processed_input[i] = '\0'; //'\0' is the sign that a string ended.
            break;
        }
    }
    //Now, your processed_input is the shit you want.

    return processed_input;
}

void inputGetterTester(void){
    printf("Testing input_getter()...\nEnter an input: ");
    char* input_char = inputGetter();
    printArray(input_char);
    printf("\n\n");
}

bool lookahead(char compared_char){
    return *nextInputChar == compared_char;
}

bool match(char compared_char){
    if (lookahead(compared_char)) {
        nextInputChar += 1;
        return true;
    } else {
        return false;
    }
}

void lookaheadMatchTester(void){
    //Testing lookahead & match
    printf("Testing lookahead & match...\nEnter an input: ");

    nextInputChar = inputGetter();

    printArray(nextInputChar);

    printf("\n");

    if (lookahead('D')){
        printf("First symbol is D");
    } else {
        printf("First symbol is not D");
    }

    printf("\n");

    if (match('R')){
        printf("First symbol is R");
    } else {
        printf("First symbol is not R");
    }

    printf("\n");

    if (match('T')){
        printf("Second symbol is T");
    } else {
        printf("Second symbol is not T");
    }
    //Testing lookahead & match
}

bool quitDetector(void){
    char* quit = "quit";
    if (strcmp(quit, nextInputChar) == 0){
        return true;
    }
    return false;
}

void quitDetectorTester(void){
    nextInputChar = inputGetter();

    if (quitDetector()){
        printf("You've inputted 'quit'");
    } else {
        printf("You didn't input 'quit'");
    }
}

TREE parse(char* input){
    nextInputChar = input;

    TREE parseTree = E();
    if (parseTree != NULL && lookahead('\0')) {
        return parseTree;
    } else {
        printf("You didn't input a well-formed bitstring!\n");
        return FAILED;
    }
}

TREE B(void){
    if (match('0')){
        return makeNode0('0');
    }
    if (match('1')){
        return makeNode0('1');
    }
    return FAILED;
}

TREE ST(void){ //ST == D
    if (!lookahead('0') && !lookahead('1')){
        return makeNode1('D', makeNode0('e'));
    } else{
        TREE y1 = S();
        if (y1 == NULL) return FAILED;
        return makeNode1('D', y1);
    }
}

TREE S(void){
    TREE y1 = B();
    if (y1 == NULL) return FAILED;
    TREE y2 = ST();
    if (y2 == NULL) return FAILED;
    return makeNode2('S', y1, y2);
}

TREE F(void){
    if (!lookahead('~') && !lookahead('(')){
        TREE y1 = S();
        if (y1 == NULL) return FAILED;
        return makeNode1('F', y1);
    }
    if (lookahead('~')){
        if (!match('~')) return FAILED;
        TREE y2 = F();
        if (y2 == NULL) return FAILED;
        return makeNode2('F', makeNode0('~'), y2);
    }
    if (lookahead('(')){
        if (!match('(')) return FAILED;
        TREE y2 = E();
        if (y2 == NULL) return FAILED;
        if (!match(')')) return FAILED;
        return makeNode3('F', makeNode0('('), y2, makeNode0(')'));
    }
    return FAILED;
}

TREE TT(void){ //TT == Y
    if (!lookahead('&')){
        return makeNode1('Y', makeNode0('e'));
    } else {
        if (!match('&')) return FAILED;
        TREE y2 = T();
        if (y2 == NULL) return FAILED;
        return makeNode2('Y', makeNode0('&'), y2);
    }
}

TREE T(void){
    TREE y1 = F();
    if (y1 == NULL) return FAILED;
    TREE y2 = TT();
    if (y2 == NULL) return FAILED;
    return makeNode2('T', y1, y2);
}

TREE ET(void){ //ET == R
    if (!lookahead('|')){
        return makeNode1('R', makeNode0('e'));
    } else {
        if (!match('|')) return FAILED;
        TREE y2 = E();
        if (y2 == NULL) return FAILED;
        return makeNode2('R', makeNode0('|'), y2);
    }
}

TREE E(void){
    TREE y1 = T();
    if (y1 == NULL) return FAILED;
    TREE y2 = ET();
    if (y2 == NULL) return FAILED;
    return makeNode2('E', y1, y2);
}

//PART II THIRD TRY (T or F)-----------------------------------------------------------------------------------
//STACK STACK STACK STACK STACK
typedef struct Stack {
    char data[MAX_SIZE];
    int top;
} Stack;

void push(Stack* stack, char c) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow!\n");
        return;
    }
    stack->data[++(stack->top)] = c;
}

char pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow!\n");
        return '\0';
    }
    return stack->data[(stack->top)--];
}

int isEmpty(Stack* stack) {
    return (stack->top == -1);
}
//STACK STACK STACK STACK STACK

void stackTester(void){
    Stack stack;
    stack.top = -1;

    push(&stack, 'a');
    push(&stack, 'b');
    push(&stack, 'c');
    push(&stack, 'd');
    push(&stack, 'e');

    while (!isEmpty(&stack)) {
        printf("%c ", pop(&stack));
    }
    printf("\n");
}

//MAP MAP MAP MAP MAP
typedef struct {
    char keys[MAP_SIZE];
    int values[MAP_SIZE];
    int size;
} Map;

void map_init(Map *map) {
    map->size = 0;
}

void map_put(Map *map, char key, int value) {
    if (map->size >= MAP_SIZE) {
        printf("Map is full, cannot add new key-value pair.\n");
        return;
    }
    for (int i = 0; i < map->size; i++) {
        if (map->keys[i] == key) {
            map->values[i] = value;
            return;
        }
    }
    map->keys[map->size] = key;
    map->values[map->size] = value;
    map->size++;
}

int map_get(Map *map, char key) {
    for (int i = 0; i < map->size; i++) {
        if (map->keys[i] == key) {
            return map->values[i];
        }
    }
    printf("Key not found.\n");
    return -1;
}

bool is_in(Map *map, char key) {
    for (int i = 0; i < map->size; i++) {
        if (map->keys[i] == key) {
            return true;
        }
    }
    return false;
}
//MAP MAP MAP MAP MAP

//Maps For This Project Maps For This Project Maps For This Project Maps For This Project Maps For This Project
Map symbolToIndex(void) {
    Map map;
    map_init(&map);
    map_put(&map, '0', 0);
    map_put(&map, '1', 1);
    map_put(&map, '(', 2);
    map_put(&map, ')', 3);
    map_put(&map, '~', 4);
    map_put(&map, '&', 5);
    map_put(&map, '|', 6);
    map_put(&map, 'e', 7);
    return map;
}
Map nntrmnlToIndex(void) {
    Map map;
    map_init(&map);
    map_put(&map, 'E', 0);
    map_put(&map, 'R', 1);
    map_put(&map, 'T', 2);
    map_put(&map, 'Y', 3);
    map_put(&map, 'F', 4);
    map_put(&map, 'S', 5);
    map_put(&map, 'D', 6);
    map_put(&map, 'B', 7);
    return map;
}
//Maps For This Project Maps For This Project Maps For This Project Maps For This Project Maps For This Project

void mapTester(void){
    Map map1, map2;
    map_init(&map1);
    map_init(&map2);
    map_put(&map1, 'a', 1);
    map_put(&map2, 'b', 2);
    printf("%d\n", map_get(&map1, 'a'));
    printf("%d\n", map_get(&map2, 'b'));
    printf("%d\n", map_get(&map1, 'b'));
    printf("%d\n", map_get(&map2, 'a'));

    if (is_in(&map1, 'a')) {
        printf("Key 'a' is in the map1.\n");
    }
    else {
        printf("Key 'a' is not in the map1.\n");
    }

    if (is_in(&map2, 'a')) {
        printf("Key 'a' is in the map2.\n");
    }
    else {
        printf("Key 'a' is not in the map2.\n");
    }
}

//PARSE TABLE PARSE TABLE PARSE TABLE PARSE TABLE PARSE TABLE
int** parseTableInitializer(void){
    int** parseTable = malloc(8 * sizeof(int*));
    for (int i = 0; i < 8; i++){
        parseTable[i] = malloc( 8 * sizeof(int));
        for (int j = 0; j < 8; j++){
            parseTable[i][j] = -1;
        }
    }
    return parseTable;
}

int** parseTableFiller(int** parseTable){
    for (int i = 0; i < 3; i++){
        parseTable[i][0] = 0;
    }
    parseTable[4][0] = 0;

    for (int i = 0; i < 6; i++){
        parseTable[i][1] = 2;
    }
    parseTable[6][1] = 1;
    parseTable[7][1] = 2;

    for (int i = 0; i < 3; i++){
        parseTable[i][2] = 3;
    }
    parseTable[4][2] = 3;

    for (int i = 0; i < 5; i++){
        parseTable[i][3] = 5;
    }
    parseTable[5][3] = 4;
    parseTable[6][3] = 5;
    parseTable[7][3] = 5;

    parseTable[0][4] = 8;
    parseTable[1][4] = 8;
    parseTable[2][4] = 7;
    parseTable[4][4] = 6;

    parseTable[0][5] = 9;
    parseTable[1][5] = 9;

    parseTable[0][6] = 10;
    parseTable[1][6] = 10;
    for (int i = 2; i < 8; i++){
        parseTable[i][6] = 11;
    }

    parseTable[0][7] = 12;
    parseTable[1][7] = 13;
    return parseTable;
}
//PARSE TABLE PARSE TABLE PARSE TABLE PARSE TABLE PARSE TABLE1
void parseTableInitializerTester(int** parseTable){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (parseTable[i][j] != -1){
                printf("Error: parse table element at (%d, %d) has incorrect value\n", i, j);
                return;
            }
        }
    }

    printf("All tests passed!\n");
}

void parseTableFillerTester(int** parseTable){
    if (parseTable[4][4] != 6){
        printf("Error at [4][4]");
        return;
    }
    if (parseTable[7][1] != 2){
        printf("Error at [7][1]");
        return;
    }
    if (parseTable[2][5] != -1){
        printf("Error at [2][5]");
        return;
    }
    printf("parseTableFiller is all good!");
}

//GRAMMAR GRAMMAR GRAMMAR GRAMMAR GRAMMAR
char** grammarArrayGenerator(void) {
    char **grammar = malloc(15 * sizeof(char *));

    for (int i = 0; i < 15; i++){
        grammar[i] = strdup("\0");
    }
    return grammar;
}

char** grammarArrayFiller(char** grammar_array){
    grammar_array[0] = strdup("TR\0");
    grammar_array[1] = strdup("|E\0");
    grammar_array[2] = strdup("e\0");
    grammar_array[3] = strdup("FY\0");
    grammar_array[4] = strdup("&T\0");
    grammar_array[5] = strdup("e\0");
    grammar_array[6] = strdup("~F\0");
    grammar_array[7] = strdup("(E)\0");
    grammar_array[8] = strdup("S\0");
    grammar_array[9] = strdup("BD\0");
    grammar_array[10] = strdup("S\0");
    grammar_array[11] = strdup("e\0");
    grammar_array[12] = strdup("0\0");
    grammar_array[13] = strdup("1\0");
    return grammar_array;
}
//GRAMMAR GRAMMAR GRAMMAR GRAMMAR GRAMMAR
void grammarArrayGeneratorTester(char** grammar){
    for (int i = 0; i < 15; i++){
        if (strcmp(grammar[i], "\0") != 0){
            printf("Error: grammar array at (%d) has incorrect value\n", i);
            return;
        }
    }

    printf("All tests passed!\n");
}
void grammarArrayFillerTester(void) {
    // Generate grammar array
    char **grammar = grammarArrayGenerator();

    // Fill grammar array using grammarArrayFiller
    grammarArrayFiller(grammar);

    // Verify that grammar array has been filled correctly
    assert(strcmp(grammar[0], "TR") == 0);
    assert(strcmp(grammar[1], "|E") == 0);
    assert(strcmp(grammar[2], "e") == 0);
    assert(strcmp(grammar[3], "FY") == 0);
    assert(strcmp(grammar[4], "&T") == 0);
    assert(strcmp(grammar[5], "e") == 0);
    assert(strcmp(grammar[6], "~F") == 0);
    assert(strcmp(grammar[7], "(E)") == 0);
    assert(strcmp(grammar[8], "S") == 0);
    assert(strcmp(grammar[9], "BD") == 0);
    assert(strcmp(grammar[10], "S") == 0);
    assert(strcmp(grammar[11], "e") == 0);
    assert(strcmp(grammar[12], "0") == 0);
    assert(strcmp(grammar[13], "1") == 0);

    // Free memory allocated for grammar array
    for (int i = 0; i < 15; i++) {
        free(grammar[i]);
    }
    free(grammar);
}

//PARSER PARSER PARSER PARSER PARSER PARSER PARSER PARSER
bool tableParse(char** grammar_array, int** parse_table, char* input, Map terminal_index, Map nntrmnl_index, char start_symbol){
    //Initialize nextInputChar.
    nextInputChar = input;

    //printf("input is: %s\n", nextInputChar); //Debugger. Remember to comment out.

    //Initialize a stack and push the start symbol to it.
    Stack parsing_stack;
    parsing_stack.top = -1;
    push(&parsing_stack, start_symbol);

    //int loop_count = 1;//Debugger. Remember to comment out.

    while (!isEmpty(&parsing_stack)){ //While stack is not empty.

        //printf("loop %d\n", loop_count);//Debugger. Remember to comment out.
        //loop_count = loop_count + 1; //Debugger. Remember to comment out.

        char current_char = pop(&parsing_stack);
        if (is_in(&nntrmnl_index, current_char)){ //If current_char is a nonter.
            //Check if current symbol is in the other map.
            int x; //x coordinate in parse table.
            if (is_in(&terminal_index, *nextInputChar)){ //If nextInputChar is in symbol_index. i.e. not e.
                //Get *nextInputChar's index.
                x = map_get(&terminal_index, *nextInputChar);
            } else { //If nextInputChar is e, symbol index is 7. (designated 'e' location)
                x = 7;
            }
            //Get current_char(non-terminal)'s index.
            int y = map_get(&nntrmnl_index, current_char);
            int grammar_index = parse_table[x][y];
            if (grammar_index == -1){
                return false;
            }
            char* current_grammar = grammar_array[grammar_index];
            //Reverse push string to stack
            int current_grammar_length = (int)strlen(current_grammar);
            for (int i = current_grammar_length - 1; i >= 0; i--){
                push(&parsing_stack, current_grammar[i]);
            }
        } else { //If current_char is a terminal.
            if (current_char == 'e'){
                nextInputChar += 1;
            }

            else if (!match(current_char)){
                return false;
            }
        }
    }

    if (lookahead('\0')){
        return true;
    }

    return false;
}
//PARSER PARSER PARSER PARSER PARSER PARSER PARSER PARSER

//PART II THIRD TRY-----------------------------------------------------------------------------------

//Main-associated methods
void partOne(void){
    printf("\nWelcome to JINGXING's Project II\nRefer to README.txt for essential info.\n");
    printf("\nHighlighted Info from README.txt:");
    printf("\n--Non-terminals <ET> <TT> <ST> are represented as <R> <Y> <D> in the parse tree!");
    printf("\n  This is because NODE's label is a char.");
    printf("\n  My naming rule is simply picking the next letter in the QWERTY keyboard for E, T, and S, respectively.");
    printf("\n  Please don't deduct my points because of the naming. It's just a name. Project requirement didn't specify this.\n\n");
    printf("Part 1\n\n");

    while (true){
        printf("Enter a bitstring input ('quit' to continue to part 2): ");
        char* input = inputGetter();

        nextInputChar = input;

        if (quitDetector()){
            printf("Moving on to part 2...\n\n");
            break;
        }

        TREE parseTree = parse(input);
        traverseLRCRS(parseTree, 0);
        printf("\n");
    }
}

void partTwo(void){
    printf("Part 2\n\n");

    while (true){
        printf("Enter a bitstring input ('quit' to end program): ");
        char* input = inputGetter();

        nextInputChar = input;

        if (quitDetector()){
            printf("Thank you for using JINGXING's Project II.\n\n");
            break;
        }

        bool parseTree2 = tableParse(grammarArrayFiller(grammarArrayGenerator()), parseTableFiller(parseTableInitializer()), input, symbolToIndex(), nntrmnlToIndex(), 'E');
        if (parseTree2){
            printf("This string is a well-formed input of the grammar!\n\n");
        } else {
            printf("This string is NOT a well-formed input of the grammar!\n\n");
        }
    }
}
//Main-associated methods

int main(void) {
    partOne();
    partTwo();
    return 0;
}
