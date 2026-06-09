+++
title = 'Mein erster Szenengraph'
draft = false
weight = 60 
+++

## Class Library

Mit den Erkenntnissen der ersten Godot-Source-Code-Analyse sollen nun die wichtigen Bestandteile in einer eigenen Applikation nachgebaut werden.

Zunächst soll die Applikation keine grafische Ausgabe erzeugen, sondern im Source-Code nur die Strukturen nachbauen. Dazu genügt es, eine Konsolen-Applikation wie die ersten "Hello, World"-Übungen zu erzeugen. Ausgaben können mit `printf` auf der Konsole dazu genutzt werden, um dem Programm beim Arbeiten zuzusehen.

In einer späteren Lektion können wir dann versuchen, dem Programm einen Unterbau unterzuschieben, der tatsächlich grafische Ausgaben erzeugt.

### Object, RefCounted, etc.

Entwirf eine an Godot's 3D-Klassen angelehnte Klassenbibliothek, die es erlaubt, aus Instanzen hierarchische Strukturen zu erzeugen. Eine Klasse namens `Node` (die aber eher an Godot's `Node3D` angelehnt ist) sollte dabei weit oben in der Hierarchie stehen. Jede Node sollte in der Lage sein, eine Liste von Kind-Nodes zu enthalten. Ebenfalls weit oben in der Klassen-Hierarchie sollten die üblichen 3D-Transformation-Eigenschaften (Position, Rotation, Skalierung) verankert sein. Implementiere eine spezielle, virtuelle Methode namens `Render` in `Node` die beim Iterieren des Szenegraphen zu Render-Zwecken aufgerufen wird.

Von `Node` abgeleitete Klassen übernehmen spezielle Aufgaben. Identifiziere einige erste "sinnvolle" Klassen, wie z. B. `MeshInstance3D` (Name darf anders sein, z.B. `MeshInstance`), die visuelle Bausteine einer 3D-Szene darstellen. Implementiere die `Render`-Methoden durch spezielle Konsolen-Ausgaben (Name, Typ und Eigenschaften der Node).

Simuliere `Resources` zunächst mit 2-3 Klasse (`Mesh`, `Texture`). Sorge dafür, dass die Lebenszeit zumindest dieser Klassen mittels Reference-Counting gemanagt wird.

### Main Loop, Iteration

Strukturiere die `main`-Funktion in einen Initialisierungs- und einen Game-Loop-Teil. Erstelle im Initialisierungs-Code einen Beispiel-Szenengraphen aus den Bestandteilen der Szenen-Klassenbibliothek. Im Rumpf der Game-Loop, traversiere den Szenengraphen und sorge dafür, dass für jede besuchte Node deren `Render`-Methode aufgerufen wird.


## Szenen-Traversierung

### Wie macht es Godot?

Versuche, herauszufinden, wie in Godot der Traversierungsmechanismus des Szenengraphen funktioniert.

- Wo ist die Liste von Kind-Objekten einer Node gespeichert?
- Finde den Code, der die Schleife enthält, die über die Kind-Liste iteriert
  - In welcher Klasse ist diese Methode enthalten?
- Welche Aktionen werden beim "Besuch" einer Node während der Traversierung ausgelöst?
- Wie ist die Polymorphie implementiert, also das z. B. beim Besuch einer `MeshInstance3D`-Node anderer Code ausgeführt wird, als beim Besuch einer `Camera3D`-Node?


### Eigene Traversierung

Um eine Szene zu rendern, muss der Szenengraph traversiert werden, d. h. beginnend beim Wurzelknoten wird jede Node des Szenengraphen besucht und aufgefordert, ihren Beitrag zum Gesamt-Renderergebnis beizutragen. Die Reihenfolge erfolgt dabei nach einer "Depth-First" Traversierung, d. h. als Folge einer gerade bearbeiteten Node wird als nächstes deren (möglicherweise vorhandenes) Kind-Objekt bearbeitet. Erst wenn eine Node keine (weiteren unbearbeiten) Kind Objekte hat, wird das nächste "Geschwister-"Objekt auf gleicher Hierarchieebene bearbeitet.

Eine solche Traversierung lässt sich rekursiv implementieren:

```c++

void Node3D::render()
{
    std::cout << "Rendering Node3D: " << getName() << std::endl;
    for (const auto &child : children) {
        child.second->render(); // Recursively render each child
    }
}

```

Im Inneren der `for`-Schleife der Methode `render` werden der Reihe nach die `render`-Methoden der Kind-Objekte aufgerufen

### Polymorphie

In Anlehnung an Godot soll ein System entstehen, in dem viele unterschiedliche von `Node3D` abgeleitete Klassen für unterschiedliche Aufgaben vorgehalten werden können. Je nach Typ muss es daher möglich sein, dass die Implementierung von `render` unterschiedlich ausgeprägt ist: Eine `MeshInstance3D` soll die ihr zugeordnete Mesh-Geometrie rendern, eine `Camera3D` soll die dort gespeicherten Kamera-Parameter (z.B. Öffnungswinkel (a.k.a "Brennweite")) setzen, eine `Node3D` selbst soll lediglich die 3D-Transformationen (Position, Rotation, Scale) setzen und die Kindliste traversieren.

Derartige Szenarien, in denen eine bestimmte Methode für unterschiedliche konkrete Ausprägungen in unterschiedlicher Weise implementiert wird, kommen häufig in objektorientierten Software-Architekturen vor. Dieses objektorientierte Prinzip ist unter dem Namen **Polymorphie** bekannt. Übersetzt bedeutet der Begriff "Vielgestaltigkeit" und bedeutet, dass unterschiedliche konkrete Implementierungen einer gemeinsamen Basisklasse sehr unterschiedliche Ausprägungen ("Gestalten") haben können.

Ein einfaches Beispiel verdeutlicht dies: Sowohl `Hund` als auch `Katze` sind `Tier`e (erben von der Basisklasse `Tier`). 

```c++
class Tier
{
public:
    virtual void TuWas()
    {
        std::cout << "Tier::TuWas aufgerufen" << std::endl;
    }
};

class Katze : public Tier
{
public:
    virtual void TuWas()
    {
        std::cout << "Katze::Miau" << std::endl;
    }    
};


class Hund : public Tier
{
public:
    virtual void TuWas()
    {
        std::cout << "Hund::Wuff" << std::endl;
    }
};
```

Das Schlüsselwort `virtual` mit dem die Methode `TuWas` dekoriert wird, sorgt dafür, dass auch in einem Kontext, in dem die konkrete Ausprägung einer `Tier`-Variablen nicht bekannt ist, die richtige Methode aufgerufen wird:

```c++

int main() {

    Tier *tier = new Tier();
    Katze *katze = new Katze();
    Hund *hund = new Hund();

    // Create an array of Tier pointers
    // and call TuWas on each of them
    Tier *tiere[] = {tier, katze, hund};
    for (Tier *t : tiere) {
        t->TuWas();
    }
}
```

Innerhalb der for-Schleife ist nur bekannt, dass der aktuell behandelte Array-Eintrag ein `Tier` ist. Trotzdem erfolgt der Aufruf der jeweils zum Typ der Instanz passenden Methode. Resultat: Der Hund bellt, die Katze miaut.

Im Fall einer Klassenbibliothek für Szenengraph-Objekte muss die Methode `render` daher ebenfalls virtuell implementiert werden und kann daher für unterschiedliche Objekttypen unterschiedlich implementiert werden.

## Visitor-Pattern 

Während der Ausführung einer interaktiven Applikation auf Basis eines Szenengraphen kann es mehrere Szenarien geben, die eine Traversierung des Graphen erfordern, z. B.

- Rendern (ein mal pro Frame)
- Ausführen eines Simulationsschrittes der Physik-Simulation
- Picking (User hat per Maus/Touch auf dem gerenderten Bild eine Auswahl getroffen, welche Objekte liegen darunter?)
- Serialisierung (Speichern, Übertragung per Netzwerk) von Szenen oder Teilen davon
- Auffinden einzelner Nodes im Szenengraphen auf Grund bestimmter Kriterien (Namen, Eigenschaften)

Statt nun für jede dieser "Traversierungsgründe" in jeder Klasse der Szenengraph-Objekttypen jeweils eine Methode vorzusehen, wird folgendermaßen verfahren:

Statt einer Anwendungsbezogenen Methode (`render`) gibt es eine polymorph (im Bezug auf die Node) implementierte Methode namens `accept`, die eine konkrete Implementierung einer Basisklasse `visitor` als Parameter entgegen nimmt. Für jeden Traversierungsgrund gibt es einen eigenen Visitor. Jeder dieser Visitor-Implementierungen sieht für jeden Node-Typen eine Methode `visit` vor. Aus der jeweiligen `accept`-Methode wird dann wiederum diese polymorph (im Bezug auf den Visitor) implementierte Methode `visit` aufgerufen. Somit wird die Notwendigkeit, die richtige Methode auf Grund von zwei konkreten Implementierungen, nämlich der konkreten Node und des konkreten Visitor (des Traversierungsgrundes) auszuwählen, durch zwei hintereinander ausgeführte polymorphe Aufrufe realisiert. Diese Doppelung führt dazu, dass dieses Verfahren auch [Double-Dispatch](https://en.wikipedia.org/wiki/Double_dispatch#:~:text=In%20software%20engineering%2C%20double%20dispatch,objects%20involved%20in%20the%20call.) genannt wird. Ein häufiger verwendeter Name für dieses Verfahren ist [Visitor-Pattern](https://en.wikipedia.org/wiki/Visitor_pattern).




## Resourcen

- [Start-Projekt für Beispiel-Szenengraph](https://github.com/griestopf/SWDevInGames_2025_SS/tree/main/_example_code/L04_Scratch)