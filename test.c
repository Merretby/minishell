#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct Token {
    int val;
    char type;
} Token;

typedef struct Node
{
    Token *token;
    struct Node *left;
    struct Node *right;
} Node;

Token *new_token(char type)
{
    Token *new = calloc(1,sizeof(Token));
    new->type = type;
    return new;
}

Token *tokens[100];
size_t pos;

void Tokenize(char *str)
{
    size_t i = 0;
    while(str[i])
    {
        if(isspace(str[i]))
        {
            i++;
            continue;
        }
        else if(isdigit(str[i]))
        {
            tokens[pos] = new_token('n');
            tokens[pos]->val = str[i] - '0';
            pos++;
            i++;
            continue;
        }
        else if(strchr("+-*/()", str[i]))
        {
            tokens[pos] = new_token(str[i]);
            pos++;
            i++;
            continue;
        }
    }
    tokens[pos++] =  new_token('e');
}

Node *new_node(Token *token)
{
    Node *new = calloc(1,sizeof(Node));
    new->token = token;
    return new;
}


Node *expr();
Node *add_sub();
Node *mul_div(); 
               
                
Node *prime(); 



Node *expr()
{
    return (mul_div());
}
 
Node *add_sub()
{
    Node *left = prime(); 
    while(tokens[pos]->type != 'e' && strchr("-+", tokens[pos]->type))
    {
        printf("found <%c>\n", tokens[pos]->type);
        Node *node = new_node(tokens[pos]);
        pos++;
        node->left = left;
        node->right = prime(); 
        left = node;
    }
    return left;
}

Node *mul_div()
{
    Node *left = add_sub(); 
    while(tokens[pos]->type != 'e' && strchr("*/", tokens[pos]->type))
    {
        printf("found <%c>\n", tokens[pos]->type);
        Node *node = new_node(tokens[pos]);
        pos++;
        node->left = left;
        node->right = mul_div(); 
        left = node;
    }
    return left;
}

Node *prime()
{
    if(tokens[pos]->type == 'n')
        return new_node(tokens[pos++]);
    if(tokens[pos]->type == 'e')
    {
        pos++;
        return NULL;
    }
    // if(tokens[pos]->type == '(')
    // {
    //     pos++;
    //     Node *node = expr();
    //     if(tokens[pos]->type != ')')
    //     {
    //         printf("Error: expected ')'\n");
    //         exit(1);
    //     }
    //     pos++;
    //     return node;
    // }
    // else
    // {
    //     printf("Error: something wrong 2");
    // }
    return NULL;
}


int eval(Node *node)
{
    char type = node->token->type;
    if(type == 'n')
        return node->token->val;
    else if(type == '+')
    {
        int left = eval(node->left);
        int right = eval(node->right);
        return left  + right;
    }
    else if(type == '-')
    {
        int left = eval(node->left);
        int right = eval(node->right);
        return left  - right;
    }
    else if(type == '*')
    {
        int left = eval(node->left);
        int right = eval(node->right);
        return left  * right;
    }
    else if(type == '/')
    {
        int left = eval(node->left);
        int right = eval(node->right);
        return left  / right;
    }
    else
    {
        printf("Error: something wrong");
        exit(1);
    }
}

// DEBUGING
void print_token(Token *token)
{
    if(token->type == 'n')
        printf("token type: number, value: %d \n", token->val);
    else if(strchr("+-/*e()", token->type))
        printf("token type: %c \n", token->type);
    else
    {
        printf("Error: unkown type\n");
        exit(1);
    }

}
void print_node(char *text, Node *node, int space)
{
    if(node)
    {
        int i = 0;
        while(i < space)
            i += printf(" ");
            if(text)
                printf("%s ", text);
        printf("node has type <%c>", node->token->type);
        if(node->token->type == 'n')
            printf(", value <%d>", node->token->val);
        printf("\n");
        print_node("left", node->left, space + 5);
        print_node("right", node->right, space + 5);
    }
}

int main()
{
    char *str = "3+1*2";
    Tokenize(str);
    size_t i = 0;
    while(i < pos)
    {
        print_token(tokens[i]);
        i++;
    }
    pos = 0;
    Node *node = expr();
    print_node(NULL, node, 0);
    int res = eval(node);
    printf("result <%d>\n", res);
   
}