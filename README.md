# Générateur-et-vérificateur-de-mots-de-passe
# Password Tool en C

Un outil en C permettant de **générer** et **vérifier la robustesse** de mots de passe. Projet éducatif en cybersécurité et programmation système.

---

## Objectifs

- Générateur de mots de passe aléatoires avec lettres, chiffres et symboles.
- Vérificateur de robustesse selon des critères classiques :
  - Longueur minimale
  - Présence de majuscules, minuscules, chiffres et symboles
- Interface en ligne de commande simple

---

## Comment lancer le projet ?

Ce projet fonctionne sur **Linux** avec `gcc`.

```bash
gcc password.c -o password
./password
