# 🎬 Gestion Cinéma

Ce projet est une application en langage C permettant la gestion complète d'un cinéma. Elle offre une interface en ligne de commande (CLI) pour gérer les films, les salles, les séances et les administrateurs, ainsi qu'une interface publique pour consulter les séances programmées.

## 🚀 Fonctionnalités

Le programme est divisé en deux sections principales :

### 1\. Interface Publique (Accueil)

  * **Consultation des séances :** Affichage des séances disponibles avec filtrage par critères (Type de siège et Type de son).
  * **Calcul automatique des prix :** Le prix est affiché dynamiquement selon les équipements de la salle (Supplément pour siège "Confort" ou son "ATMOS").
  * **Connexion Administrateur :** Accès sécurisé aux fonctions de gestion.

### 2\. Interface Administrateur

Une fois connecté, un administrateur peut effectuer les opérations CRUD (Create, Read, Update, Delete) suivantes :

  * **Gestion des Séances :** Planifier une séance en liant un film existant à une salle et une heure donnée.
  * **Gestion des Films :** Ajouter, modifier ou supprimer des films (Titre et Durée).
  * **Gestion des Salles :** Configurer les salles (Capacité, Type de siège, Type de son).
  * **Gestion des Administrateurs (Super-Admin uniquement) :** Ajouter ou supprimer d'autres administrateurs. Cette fonctionnalité est protégée par une seconde authentification.

## 🛠️ Prérequis et Installation

### Compilation

Le projet ne nécessite aucune librairie externe non standard. Il peut être compilé avec `gcc`.

```bash
gcc projet2.0.c -o gestion-cinema
```

### Fichiers de données

Le programme utilise un système de persistance binaire. **Important :** Pour que le programme démarre, les 4 fichiers suivants doivent impérativement exister dans le même répertoire que l'exécutable:

  * `admins.dat` : Stocke les identifiants administrateurs.
  * `films.dat` : Stocke la liste des films.
  * `salles.dat` : Stocke la configuration des salles.
  * `seances.dat` : Stocke la programmation.

> **Note :** Si ces fichiers sont absents, le programme affichera un message d'erreur et se fermera immédiatement.

## 👤 Utilisation et Identifiants

### Lancer le programme

```bash
./gestion-cinema
```

### Comptes par défaut

Voici les comptes utilisables pour tester l'application :

| Rôle | Identifiant (User) | Mot de passe | Notes |
| :--- | :--- | :--- | :--- |
| **Admin** | `Antoine` | `A0204` | Compte standard |
| **Admin** | `Loris` | `L0204` | Compte standard |
| **Admin** | `Bryan` | `B0204` | Compte standard |
| **Super Admin** | `admin` | `admin` | Requis pour gérer les comptes admins |

## 💾 Structure des Données

Les informations sont stockées sous forme de structures C sérialisées dans des fichiers binaires (`.dat`) :

  * **`struct film`** : ID, Titre, Durée.
  * **`struct salle`** : ID, Capacité, Type de siège (Standard/Confort), Type de son (Standard/ATMOS).
  * **`struct seance`** : ID, ID du film, ID de la salle, Heure de début.
  * **`struct admin`** : Nom d'utilisateur, Mot de passe.

*Le programme utilise des tableaux statiques (limite de 100 éléments) pour les films, salles et séances, et une allocation dynamique pour la liste des administrateurs.*

## 👥 Auteurs

Projet réalisé dans le cadre académique (HEPH - Condorcet), lors de la 1ère année de Bachelier.
