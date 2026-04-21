+++
title = 'Erste Schritte im Godot-Source-Code'
draft = false
weight = 50 
+++

## Godot Bauen

- Der Anleitung [Building from Source](https://docs.godotengine.org/en/stable/contributing/development/compiling/index.html#) folgen
- Hintergrundinfo zum Build-System: [Introduction to the build system](https://docs.godotengine.org/en/stable/contributing/development/compiling/introduction_to_the_buildsystem.html)

- Die wesentlichen Schritte zum Bauen sind:
    - Github-Repo clonen: https://github.com/godotengine/godot
    - scons (Buildsystem) installieren
    - Build Godot for debugging: 
    ```scons dev_build=yes debug_symbols=yes```
    - Generate vsproj and sln files: 
    ```scons platform=windows vsproj=yes```
    - Dann Verzeichnis mit VS-Code aus der Developer-Console öffnen 

- Im Godot-Source-Verzeichnis im Unterverzeichnis `.vscode` die Datei tasks.json mit folgendem Inhalt anlegen:

    ```json
    {
        "version": "2.0.0",
        "tasks": [
            {
                "type": "shell",
                "label": "SCons: build",
                "command": "scons",
                "args": [
                    "dev_build=yes",
                    "debug_symbols=yes",
                    "platform=windows"
                ],
                "group": {
                    "kind": "build",
                    "isDefault": true
                },
                "problemMatcher": [],
                "detail": "Build Godot with SCons"
            }
        ]
    }
    ```

- In der Debug-Pane eine launch.json erzeugen, z. B. so:
    ```json
    {
        // Use IntelliSense to learn about possible attributes.
        // Hover to view descriptions of existing attributes.
        // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
        "version": "0.2.0",
        "configurations": [
        {
            "name": "(Windows) Launch",
            "type": "cppvsdbg",
            "request": "launch",
            "program": "${workspaceFolder}/bin/godot.windows.editor.dev.x86_64.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "C:/Temp/GodotSrcPrj/godotproj01", // "${fileDirname}",
            "environment": [],
            "console": "externalTerminal"
        }
        ]
    }
    ```
    - Eintrag `"program"` enthält den Pfad zum vom Compiler erzeugten Godot-Executable
    - Eintrag `"cwd"` enthält einen Pfad auf das Test-Projekt (s.u.). Damit startet Godot NICHT im Editor-Modus, sondern als Applikation. 
- Testen, ob sich Godot aus VS Code im Debug-Modus starten lässt und ob sich z. B. Breakpoints setzen lassen.

## Test-Godot-Projekt aufsetzen

- Mit der selbst gebauten Godot-Version ein einfaches Test-Projekt erzeugen
  - Einzelne 3D-Szene
  - Überschaubare Inhalte (ein paar Cubes, Environment, Licht und Kamera)
- Für den Windows-Export vorbereiten
- Abspeichern


## Erste Schritte

Interaktive Software wie Games laufen nach der Initialisierung der Teilsysteme innerhalb einer großen umgebenden Schleife ab. Die grobe Struktur eines Games ist:

```c++
void main() {
    initialize_everything();

    while (true) { // loop forever
        process_input();
        render();
    }
}
```


### Wo ist `main`?

- Finde "die" main-Methode - den Einstiegspunkt der Applikation. Setze dort einen Breakpoint und versuche, einen sehr groben Überblick über die dort implementierten initialen Abläufe zu bekommen. *Warnung*: es wird vermutlich kaum möglich sein, auch nur ansatzweise zu verstehen, was dort alles passiert.

### Wo ist die _Game Loop_?

- Versuche, Code-Teile zu finden, die offenbar innerhalb der Game-Loop laufen (z. B., weil die Auführung an einem gesetzten Breakpoint immer wieder stoppt). 

Um obige Aufgaben zu bewältigen, ist Detektivarbeit gefragt. Eine Herangehensweise ist, zunächst im Quellcode aufgrund von Dateinamen, darin dann Klassen- und Methodennamen nach möglicherweise passenden Code-Stellen zu suchen. Diese können dann durch testweise Setzen von Breakpoints in "verdächtigen" Code-Teilen überprüft werden. Der Call-Stack gibt dann Hinweise auf die Aufruf-Reihenfolge. Durchsteppen durch den Code schafft möglicherweise mehr Klarheit. U. u. hilft auch der Co-Pilot, Codeteile zu verstehen.

## Die wichtigsten Bausteine des Szenengraphen

In Godot sind die C++-Klassen, die die Bausteine einer Godot-Applikation bilden, direkt auch im Game-Editor sicht- und anwendbar. Daher kann auch in der Nutzer-Dokumentation die Klassenhierarchie abgelesen werden. Zum Verständnis, wie in Godot Szene aufgebaut sind, sollten folgende Klassen untersucht werden:

- `Object`
- `RefCounted`, und `Ref`, sowie `Resource` und Abkömmlinge
- `Node`, `Node3D` und Abkömmlinge


### Fragen/Aufgaben

Folgende Tätigkeiten sind durchzuführen

- Die Beschreibung der o. g. Klassen in der Godot-Doku lesen.
- Die Klassen im Godot-Source-Code suchen. Dazu in VS-Code `Ctrl+T` auslösen und nach den Klassennamen suchen.
- Einen Vererbungsbaum aufstellen, in dem die o. g. Klassen vorkommen

Zu beantwortende Fragen

- Warum erbt Node nicht von RefCounted? Welche Implikation in Bezug auf die Speicherveraltung sämtlicher im Szenengraph vorkommenden Objekte ergibt sich daraus?
- Wie funktioniert das Reference Counting von Ressourcen mittels der Klassen `RefCounted` und `Ref`?
  - Einblick in den Mechanismus könnte über Debugging in die Methoden `ref` und `unref` gewonnen werden.
- Wer ist "Owner" (im Sinne von Erzeugung und Löschung) sämtlicher in einer Szene lebenden Nodes? 
  - Eine Antwort auf diese Frage könnte ein Breakpoint im Konstruktor und Destruktor von Node oder einer davon abgeleiteten Klasse und ein Umschauen im Call-Stack geben.




