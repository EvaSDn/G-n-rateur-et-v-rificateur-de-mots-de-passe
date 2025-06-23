#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_PASSWORD_LENGTH 256
#define MIN_PASSWORD_LENGTH 8

// Jeux de caractères pour la génération
const char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
const char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char digits[] = "0123456789";
const char symbols[] = "!@#$%^&*()-_=+[]{}|;:,.<>?";

typedef struct {
    int has_lowercase;
    int has_uppercase;
    int has_digit;
    int has_symbol;
    int length;
    int score;
} PasswordStrength;

void generate_password(int length, int use_symbols) {
    if (length < MIN_PASSWORD_LENGTH) {
        printf("⚠️  Longueur minimale : %d caractères\n", MIN_PASSWORD_LENGTH);
        return;
    }
    
    char password[MAX_PASSWORD_LENGTH];
    char charset[256] = "";
    
    strcat(charset, lowercase);
    strcat(charset, uppercase);
    strcat(charset, digits);
    
    if (use_symbols) {
        strcat(charset, symbols);
    }
    
    int charset_len = strlen(charset);
    
    for (int i = 0; i < length; i++) {
        password[i] = charset[rand() % charset_len];
    }
    password[length] = '\0';
    
    if (length >= 4) {
        password[0] = lowercase[rand() % strlen(lowercase)];
        password[1] = uppercase[rand() % strlen(uppercase)];
        password[2] = digits[rand() % strlen(digits)];
        if (use_symbols && length > 4) {
            password[3] = symbols[rand() % strlen(symbols)];
        }
        
        for (int i = 0; i < length; i++) {
            int j = rand() % length;
            char temp = password[i];
            password[i] = password[j];
            password[j] = temp;
        }
    }
    
    printf("Mot de passe obtenue : %s\n", password);
}

PasswordStrength analyze_password(const char* password) {
    PasswordStrength strength = {0, 0, 0, 0, 0, 0};
    
    strength.length = strlen(password);
    
    for (int i = 0; i < strength.length; i++) {
        char c = password[i];
        
        if (islower(c)) {
            strength.has_lowercase = 1;
        } else if (isupper(c)) {
            strength.has_uppercase = 1;
        } else if (isdigit(c)) {
            strength.has_digit = 1;
        } else if (strchr(symbols, c)) {
            strength.has_symbol = 1;
        }
    }
    
    strength.score = 0;
    
    if (strength.length >= MIN_PASSWORD_LENGTH) strength.score += 2;
    if (strength.length >= 12) strength.score += 1;
    if (strength.length >= 16) strength.score += 1;
    
    if (strength.has_lowercase) strength.score += 1;
    if (strength.has_uppercase) strength.score += 1;
    if (strength.has_digit) strength.score += 1;
    if (strength.has_symbol) strength.score += 2;
    
    return strength;
}

void display_strength_analysis(const char* password) {
    PasswordStrength strength = analyze_password(password);
    
    printf("\nAnalyse de robustesse pour : %s\n", password);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    printf("Longueur : %d caractères ", strength.length);
    if (strength.length >= MIN_PASSWORD_LENGTH) {
        printf("OK\n");
    } else {
        printf("Non correcte (minimum %d)\n", MIN_PASSWORD_LENGTH);
    }
    
    printf("Minuscules : %s\n", strength.has_lowercase ? "Présent" : "Ajouté");
    printf("Majuscules : %s\n", strength.has_uppercase ? "Présent" : "Ajouté");
    printf("Chiffres : %s\n", strength.has_digit ? "Présent" : "Ajouté");
    printf("Symboles : %s\n", strength.has_symbol ? "Présent" : "Ajouté");
    
    printf("\nScore de fiabilité : %d/8\n", strength.score);
    
    if (strength.score >= 7) {
        printf("Mot de passe TRÈS FORT\n");
    } else if (strength.score >= 5) {
        printf("Mot de passe FORT\n");
    } else if (strength.score >= 3) {
        printf("Mot de passe MOYEN\n");
    } else {
        printf("Mot de passe FAIBLE\n");
    }
    
    printf("\nRecommandations :\n");
    if (strength.length < MIN_PASSWORD_LENGTH) {
        printf("• Augmentez la longueur (minimum %d caractères)\n", MIN_PASSWORD_LENGTH);
    }
    if (!strength.has_lowercase) {
        printf("• Ajoutez des lettres minuscules\n");
    }
    if (!strength.has_uppercase) {
        printf("• Ajoutez des lettres majuscules\n");
    }
    if (!strength.has_digit) {
        printf("• Ajoutez des chiffres\n");
    }
    if (!strength.has_symbol) {
        printf("• Ajoutez des symboles (!@#$%^&*...)\n");
    }
    if (strength.length < 12) {
        printf(" • Visez 12+ caractères pour une sécurité optimale\n");
    }
}

void display_menu() {
    printf("\nGénérateur et Vérificateur\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("1. Générer un mot de passe\n");
    printf("2. Vérifier la robustesse d'un mot de passe\n");
    printf("3. Aide\n");
    printf("4. Quitter\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Votre choix : ");
}

void display_help() {
    printf("\nAIDE - Password Tool\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Ce programme permet de :\n");
    printf("• Générer des mots de passe sécurisés\n");
    printf("• Analyser la robustesse de vos mots de passe existants\n\n");
    
    printf("Critères de robustesse :\n");
    printf("• Longueur minimale : %d caractères\n", MIN_PASSWORD_LENGTH);
    printf("• Présence de minuscules (a-z)\n");
    printf("• Présence de majuscules (A-Z)\n");
    printf("• Présence de chiffres (0-9)\n");
    printf("• Présence de symboles (!@#$%^&*...)\n\n");
    
    printf("Conseils de sécurité :\n");
    printf("• Utilisez des mots de passe uniques pour chaque compte\n");
    printf("• Visez 12+ caractères pour une sécurité optimale\n");
    printf("• Évitez les informations personnelles\n");
    printf("• Utilisez un gestionnaire de mots de passe\n");
}

int main() {
    srand(time(NULL));
    
    int choice;
    char password[MAX_PASSWORD_LENGTH];
    int length, use_symbols;
    
    printf("Bienvenue dans Password Tool !\n");
    
    while (1) {
        display_menu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Merci de faire un choix parmi la liste (1-4).\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("\nGÉNÉRATION DE MOT DE PASSE\n");
                printf("Longueur souhaitée (min %d) : ", MIN_PASSWORD_LENGTH);
                scanf("%d", &length);
                
                printf("Inclure des symboles ? (1=Oui, 0=Non) : ");
                scanf("%d", &use_symbols);
                
                printf("\n");
                generate_password(length, use_symbols);
                break;
                
            case 2:
                printf("\nVÉRIFICATION DE ROBUSTESSE\n");
                printf("Entrez votre mot de passe : ");
                scanf("%s", password);
                
                display_strength_analysis(password);
                break;
                
            case 3:
                display_help();
                break;
                
            case 4:
                printf("Restez en sécurité !\n");
                return 0;
                
            default:
                printf("Choix invalide. Veuillez sélectionner 1-4.\n");
                break;
        }
        
        printf("\nAppuyez sur Entrée pour continuer...");
        while (getchar() != '\n'); 
        getchar(); 
    }
    
    return 0;
}
