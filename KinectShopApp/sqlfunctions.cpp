#include "sqlfunctions.h"

sqlfunctions::sqlfunctions(){
    // LfB-Datenbank
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("kinectsrv.lfb.rwth-aachen.de");
    db.setDatabaseName("kinectshop2015");
    db.setUserName("kinectshopClient");
    db.setPassword("lfb-student2015");
    db.setPort(3306);

    /* // lokale Datenbank
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("kinectshop2015");
    db.setUserName("root");
    db.setPassword("");
    db.setPort(3305);
    */

    if(!db.open()){
        QMessageBox msgBox;
        msgBox.setText("Es konnte leider keine Verbindung zur SQL-Datenbank hergestellt werden!");
        msgBox.exec();
    }

    /* // Ausgabe wenn Verbindung hergestellt wurde
    else{
        QMessageBox msgBox;
        msgBox.setText("Die Verbindung zu " + db.hostName() + " wurde hergestellt.");
        msgBox.exec();
    }*/

    isLogin = false;
    isAdminLoggedIn = false;  
    uid = -1;

    badTries = 0;
    allowedAgain = 0;

    currentCartValue = 0;
}

// ----------------------------------------------------------------------------------
// --------------------------------------WAREZMGMT-----------------------------------
// ----------------------------------------------------------------------------------

// Zeige die im Shop verfügbaren Produkte an
QString sqlfunctions::listAllProducts(){
    QSqlQuery query;

    // Alles Abfragen
    query.prepare("SELECT id, title, price, stock FROM products ORDER BY products.id ASC");
    query.exec();

    int pid, stock;
    string title;
    double price;

    stringstream stream;

    // Alles darstellen
    stream  <<  "<table id='cartList' class='sortable'>"
            <<  "<thead>"
            <<  "<tr>"
            <<  "<th data-sort='number'     class='sortByPid ascending'>"      <<  "PID"    <<  "</th>"
            <<  "<th data-sort='name'       class='sortByName'>"     <<  "Produktname"   <<  "</th>"
            <<  "<th data-sort='number'     class='sortByPrice'>"    <<  "Preis"         <<  "</th>"
            <<  "<th data-sort='number'     class='sortByStock'>"    <<  "Verfügbar"     <<  "</th>"
            <<  "<th class='no-sort'>"   <<  "Menge"         <<  "</th>"
            <<  "</tr>"
            <<  "</thead>"
            <<  "<tbody>"
            <<  endl;

    while(query.next()){
        pid = query.value(0).toInt();
        title = query.value(1).toString().toStdString();
        price = query.value(2).toDouble();
        stock = query.value(3).toInt();
        stream  <<  "<tr>"
                <<  "<td>"      <<  pid       <<    "</td>"
                <<  "<td>"      <<  title     <<    "</td>"
                <<  "<td>"      <<  price     <<    "</td>"
                <<  "<td>"      <<  stock     <<    "</td>"
                <<  "<td>"      <<  "<input type='text' value='0' id='cartItemAmount"  <<   pid  <<  "'>"
                <<  "<button class='orange-button' id='buyCartItem"                    <<   pid  <<  "'>"
                <<  "in den <span class='fa fa-shopping-cart'></span></button>"        <<   "</td>"
                <<  "</tr>"
                <<  endl;
        // Das funktioniert nur, weil alle ItemIds ab 1 vorkommen
        // und die SQL-Tabelle genau in dieser Reihenfolge sortiert ist.
    }

    stream  <<  "</tbody>"
            <<  "</table>"  <<  endl;


    string s = stream.str();

    // Testfunktion
    // cout    << s    << endl;

    QString htmlOutput = QString::fromStdString(s);

    /* // Test
    QMessageBox msgBox;
    msgBox.setText(htmlOutput);
    msgBox.exec();
    */

    return htmlOutput;
}

QString sqlfunctions::listAllProducts(QString mode){
    QSqlQuery query;

    // Alles Abfragen
    query.prepare("SELECT id, title, price, stock FROM products ORDER BY products.id ASC");
    query.exec();

    int pid, stock;
    string title;
    double price;

    stringstream stream;

    // Alles darstellen
    stream  <<  "<table id='cartList' class='sortable'>"
            <<  "<thead>"
            <<  "<tr>"
            <<  endl;

    if(mode == "checkboxes"){
        stream  <<  "<th class='no-sort'></th>"
                <<  endl;
    }

    stream  <<  "<th data-sort='number'     class='sortByPid ascending'>"      <<  "PID"    <<  "</th>"
            <<  "<th data-sort='name'       class='sortByName'>"     <<  "Produktname"   <<  "</th>"
            <<  "<th data-sort='number'     class='sortByPrice'>"    <<  "Preis"         <<  "</th>"
            <<  "<th data-sort='number'     class='sortByStock'>"    <<  "Verfügbar"     <<  "</th>"
            <<  endl;

    if(mode == " "){
        stream  <<  "<th class='no-sort'>"   <<  "Menge"         <<  "</th>"
                <<  endl;
    }

    stream  <<  "</tr>"
            <<  "</thead>"
            <<  "<tbody>"
            <<  endl;

    while(query.next()){
        pid = query.value(0).toInt();
        title = query.value(1).toString().toStdString();
        price = query.value(2).toDouble();
        stock = query.value(3).toInt();
        stream  <<  "<tr>"
                <<  endl;
        if(mode == "checkboxes"){
            stream  <<  "<td>"      <<  "<input type='checkbox' name='wareSelect' id='user"
                    <<  pid         <<  "' value='"  <<     pid          <<  "'>"
                    <<  "</td>"
                    <<  endl;
        }
        stream  <<  "<td>"      <<  pid       <<    "</td>"
                <<  "<td>"      <<  title     <<    "</td>"
                <<  "<td>"      <<  price     <<    "</td>"
                <<  "<td>"      <<  stock     <<    "</td>"
                <<  endl;

        if(mode == " "){
            stream  <<  "<td>"      <<  "<input type='text' value='0' id='cartItemAmount"  <<   pid  <<  "'>"
                    <<  "<button class='orange-button' id='buyCartItem"                    <<   pid  <<  "'>"
                    <<  "in den <span class='fa fa-shopping-cart'></span></button>"        <<   "</td>"
                    <<  endl;
        }

        stream  <<  "</tr>"
                <<  endl;

        // Das funktioniert nur, weil alle ItemIds ab 1 vorkommen
        // und die SQL-Tabelle genau in dieser Reihenfolge sortiert ist.
    }

    stream  <<  "</tbody>"
            <<  "</table>"  <<  endl;

    if(mode == "checkboxes"){
        stream  <<  "<p>"
                <<  "<input type='checkbox' id='wareSelect' class='selectAll'>"
                <<  "Alle auswählen </p>"
                <<  endl;
    }


    string s = stream.str();

    // Testfunktion
    // cout    << s    << endl;

    QString htmlOutput = QString::fromStdString(s);

    /* // Test
    QMessageBox msgBox;
    msgBox.setText(htmlOutput);
    msgBox.exec();
    */

    return htmlOutput;
}

// Füge Element in den Warenkorb ein
void sqlfunctions::addToCart(int pid, int amount, double price, QString title){

    product myProduct;
    myProduct.setAmount(amount);
    myProduct.setPid(pid);
    myProduct.setPrice(price);
    myProduct.setTitle(title);

    product newProduct = isAlreadyInCart(pid, amount, price, title);
    cart.push_back(newProduct);

    /* Testfunktion ob JS-Übergabe funktioniert hat
    QMessageBox msgBox;
    msgBox.setText(QString::number(myProduct.getAmount()));
    msgBox.exec();
    */
    emit cartChanged();
}

// Überprüft, ob ein Element bereits im Warenkorb ist, falls ja erhöhe nur die Menge
// Gibt hinzuzufügendes Produkt an addToCart() zurück.
product sqlfunctions::isAlreadyInCart(int pid, int amount, double price, QString title){

    product myProduct;
    myProduct.setAmount(amount);
    myProduct.setPid(pid);
    myProduct.setPrice(price);
    myProduct.setTitle(title);

    iter cursor = find(cart.begin(), cart.end(), myProduct.getPid());
    if(cursor!=cart.end()){
        int newAmount = myProduct.getAmount() + cursor->getAmount();
        myProduct.setAmount(newAmount);
        cart.erase(cursor);
    }
    return myProduct;
}

// Gibt den Inhalt des Einkaufswagens aus
QString sqlfunctions::showCart(){

    stringstream stream;

    // Alles darstellen
    stream  <<  "<table id='productList' class='sortable'>"
            <<  "<thead>"
            <<  "<tr>"
            <<  "<th data-sort='number' class='sortByPid'>"         <<  "PID"     <<  "</th>"
            <<  "<th data-sort='name'   class='sortByName'>"        <<  "Produktname"    <<  "</th>"
            <<  "<th data-sort='number' class='sortByPrice'>"       <<  "Preis"          <<  "</th>"
            <<  "<th class='no-sort'>"                              <<  "Bestellmenge"   <<  "</th>"
            <<  "<th data-sort='number' class='sortByTotal'>"       <<  "Gesamtpreis"    <<  "</th>"
            <<  "</tr>"
            <<  "</thead>"
            <<  "<tbody>"
            <<  endl;

    int pid, amount;
    string title;
    double price, subtotal;
    currentCartValue = 0;

    for(iter cursor = cart.begin();cursor!=cart.end();cursor++){
        pid = cursor->getPid();
        title = cursor->getTitle().toStdString();
        price = cursor->getPrice();
        amount = cursor->getAmount();
        subtotal = price*amount;
        currentCartValue += subtotal;

        stream  <<  "<tr>"
                <<  "<td>"      <<  pid       <<    "</td>"
                <<  "<td>"      <<  title     <<    "</td>"
                <<  "<td>"      <<  price     <<    "</td>"
                <<  "<td>"      <<  amount
                <<  "<input type='text' value='0' id='itemAmount"  <<   pid  <<  "'>"
                <<  "<button class='orange-button' id='removeItem" <<   pid  <<  "'>"
                <<  "entfernen aus <span class='fa fa-shopping-cart'></span></button>"
                <<  "</td>"
                <<  "<td>"      <<  subtotal     <<    "</td>"
                <<  "</tr>"
                <<  endl;
    }

    stream  <<  "<tr id='total-preview' class='no-sort'>"
            <<  "<td colspan='4' style='text-align:right'>"       <<  "Gesamtpreis "      <<  "</td>"
            <<  "<td>"                                            <<  currentCartValue    <<  "</td>"
            <<  "</tr>"
            <<  "</tbody>"
            <<  "</table>"  <<  endl;

    string s = stream.str();

    // Testfunnktion
    // cout << s << endl;

    QString htmlOutput = QString::fromStdString(s);
    return htmlOutput;
}


// Leert den Einkaufswagen
void sqlfunctions::clearCart(){
    int size = cart.size();
    while(size){
        cart.pop_back();
        --size;
    }
    emit cartChanged();
}

// Wenn man unzufrieden ist mit der Menge an eingekauften Waren, kann man diese ändern.
// Überladene Funktion
void sqlfunctions::changeAmount(int pid, QString mode){
        if(mode=="clear"){
            iter cursor = find(cart.begin(), cart.end(), pid);
            double value = (cursor->getAmount())*(cursor->getPrice());
            currentCartValue -= value;
            cart.erase(cursor);
        }
        emit cartChanged();
}

void sqlfunctions::changeAmount(int pid, int diff, QString modeQString){

    string mode = modeQString.toStdString();

    iter cursor = find(cart.begin(), cart.end(), pid);

    if(mode=="add"){
        cursor->setAmount(cursor->getAmount()+diff);
        currentCartValue += diff*(cursor->getAmount())*(cursor->getPrice());
    }
    else if(mode=="sub"){
        // guckt, ob der Kunde überhaupt soviel im Warenkorb hat
        if(cursor->getAmount() < diff){
            QMessageBox msgBox;
            msgBox.setText("Sie können maximal " + QString::number(cursor->getAmount()) + " aus dem Warenkorb entfernen.");
            msgBox.exec();
            return;
        }

        // guckt, ob nach der Entferung noch etwas von der Waren übrig ist
        // falls nein
        if(cursor->getAmount() == diff){
            changeAmount(pid, "clear");
            return;
        }
        // falls ja
        cursor->setAmount(cursor->getAmount()-diff);
        currentCartValue -= diff*(cursor->getAmount())*(cursor->getPrice());
    }
    emit cartChanged();
}

// Prüft für jede Ware im Warenkorb, ob noch genug Waren vorhanden sind
int sqlfunctions::checkStock(){
    QSqlQuery query;
    int diff, stock;
    for(iter cursor = cart.begin();cursor!=cart.end();cursor++){
        query.prepare("SELECT stock FROM products WHERE id = :input");
        query.bindValue(":input", cursor->getPid());
        query.exec();      
        query.next();
        stock = query.value(0).toInt();
        diff = stock - cursor->getAmount();
    }
    return diff;
}

// Prüft, ob der Benutzer ausreichend Guthaben zum Kauf hat.
double sqlfunctions::checkBalance(){
    QSqlQuery query;
    // ermittelt Gesamtkosten des Warenkorbs
    double total = 0;
    for(iter cursor = cart.begin(); cursor!=cart.end(); cursor++){
        total += (cursor->getPrice() * cursor->getAmount());
    }
    // Vergleiche Guthaben mit Gesamtkosten
    query.prepare("SELECT balance FROM users WHERE id = :uid");
    query.bindValue(":uid", uid);
    query.exec();
    query.next();
    double balance = query.value(0).toDouble();

    /* // Testfunktion
    QMessageBox msgBox;
    msgBox.setText(QString::number(balance)+" "+QString::number(uid));
    msgBox.exec(); */

    return balance - total;
}

bool sqlfunctions::isCartEmpty(){
    if(cart.empty()){
        return true;
    }
    else{
        return false;
    }
}

// Die Bezahlfunktion
// zu checken: User eingeloggt, Einkaufswagen nicht leer, genug Waren vorhanden, genug Guthaben
bool sqlfunctions::purchase(){

    if(isCartEmpty()){
       QMessageBox msgBox;
        msgBox.setText("Der Einkaufswagen ist leer!");
        msgBox.exec();
        return false;
    }

    QSqlQuery query;
    // Überprüfe, ob User eingeloogt ist.
    if(isLogin){
        int hasEnoughMoney = checkBalance();
        // Überprüfe ob User genug Guthaben hat.
        if(hasEnoughMoney >= 0){
            // Überprüfe, ob genug waren vorhanden sind.
            int diff = checkStock();
            if(diff >= 0){

                int pid, amount, insertId, stock;
                double balance;

                for(iter cursor = cart.begin(); cursor != cart.end(); ++cursor){

                    pid = cursor->getPid();
                    amount = cursor->getAmount();

                    // SQL-Befehle für den Bezahlvorgang
                    // Buchungstabelle
                    // größte Buchungsnummer ermitteln
                    query.prepare("SELECT MAX(id) FROM bookings");
                    query.exec();
                    query.next();
                    insertId = query.value(0).toInt();
                    // Buchungsnummer um 1 erhöhen
                    insertId++;
                    query.prepare("INSERT INTO bookings (id,uid,pid,amount) VALUES (:id, :uid, :pid, :amount)");
                    query.bindValue(":id", insertId);
                    query.bindValue(":uid", uid);
                    query.bindValue(":pid", pid);
                    query.bindValue(":amount", amount);
                    query.exec();

                    // Produktvorrat reduzieren
                    query.prepare("SELECT stock FROM products WHERE id = :pid");
                    query.bindValue(":pid", pid);
                    query.exec();
                    query.next();
                    stock = query.value(0).toInt();
                    stock -= amount;

                    query.prepare("UPDATE products SET stock=:newStock WHERE id=:pid");
                    query.bindValue(":newStock", stock);
                    query.bindValue(":pid", pid);
                    query.exec();
                }

                // Geld von Useraccount abheben
                query.prepare("SELECT balance FROM users WHERE id = :uid");
                query.bindValue(":uid", uid);
                query.exec();
                query.next();
                balance = query.value(0).toDouble();
                balance -= currentCartValue;

                // Userguthaben abbuchen
                query.prepare("UPDATE users SET balance=:newBalance WHERE id =:uid");
                query.bindValue(":newBalance", balance);
                query.bindValue(":uid", uid);
                query.exec();

                // Signal: Einkauf abgeschlossen, Einkaufswagen leeren
                emit purchaseDone(cart);
                emit balanceChanged((-1)*currentCartValue);

                QMessageBox msgBox;
                QString thankYou ="<p><b> Vielen Dank für Ihren Einkauf! Sie kauften: </b><br></p>";
                msgBox.setText(thankYou+showCart());
                msgBox.exec();

                currentCartValue = 0;
                clearCart();
                return true;
            }
            else{
                // Ausgabe falls nicht genug Waren zur Verfügung stehen.
                // Füge noch die Ausgabe der (tlw.) nicht lieferbare Waren und deren vorhandene Menge
                QMessageBox msgBox;
                msgBox.setText("Es sind nicht genug Waren vorhanden. Verringern Sie ihre Bestellung um "+QString::number(diff*(-1))+" Einheiten.");
                msgBox.exec();
                return false;
            }
        }
        else{
            // Ausgabe falls der User nicht genug Geld hat.
            // User hat nicht genug Geld, zeige Differenz an.
            QMessageBox msgBox;
            msgBox.setText("Sie haben nicht genug Guthaben. Ihnen fehlen "+QString::number(hasEnoughMoney*(-1))+" Geldeinheiten.");
            msgBox.exec();
            return false;
        }
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Loggen Sie sich bitte ein, um zu bezahlen!");
        msgBox.exec();
        return false;
    }
}

// ----------------------------------------------------------------------------------
// ---------------------------------------USERMGMT-----------------------------------
// ----------------------------------------------------------------------------------

// erfordert auf Javascript-Seite noch einiges an Arbeit!
void sqlfunctions::registerUser(QString username, QString password, QString repeatedPassword){

    if(password.toStdString() == "" || username.toStdString() == "" || repeatedPassword.toStdString() == ""){
        QMessageBox msgBox;
        msgBox.setText("Ihre Angaben sind unvollständig!");
        msgBox.exec();
        return;
    }

    if(password.toStdString() != repeatedPassword.toStdString()){
        QMessageBox msgBox;
        msgBox.setText("Die Passwörter stimmen nicht überein!");
        msgBox.exec();
        return;
    }

    // Check erfolgreich
    // Überprüfen, ob User in DB vorhanden ist
    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE username = :username");
    query.bindValue(":username", username);
    query.exec();
    query.next();
    QString dbUsername = query.value(0).toString();
    // Wenn ja, trage in DB ein und gebe Erfolgsmeldung aus.
    if(username.toStdString() != dbUsername.toStdString()){
        // Maximale Usernummer herausfinden
        query.prepare("SELECT MAX(id) FROM users");
        query.exec();
        query.next();
        int insertId = query.value(0).toInt();
        // Usernummer um 1 erhöhen
        insertId++;
        query.prepare("INSERT INTO users (id, username, password, balance, isAdmin, changePasswordMode) VALUES (:insertId, :username, :password, :balance, :isAdmin, :changePasswordMode)");
        query.bindValue(":id", insertId);
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        query.bindValue(":balance", 0);
        query.bindValue(":isAdmin", 0);
        query.bindValue(":changePasswordMode", "n");
        query.exec();
        QMessageBox msgBox;
        msgBox.setText("Herzlichen Dank für Ihre Registrierung.");
        msgBox.exec();
    }

    // Wenn nicht, gib Fehlermeldung aus.
    else{
        QMessageBox msgBox;
        msgBox.setText("Das hat leider nicht funktioniert. Es gibt bereits einen Benutzer mit diesem Namen.");
        msgBox.exec();
    }
}

// gibt Tabelle mit allen Usern für Adminstration aus
QString sqlfunctions::listAllUsers(){

    QSqlQuery query;
    stringstream stream;

    stream  <<  "<table id='users' class='sortable'>"
            <<  "<thead>"
            <<  "<tr>"
            <<  "<th class='no-sort'></th>"
            <<  "<th data-sort='number'>"          <<  "ID"                <<  "</th>"
            <<  "<th data-sort='name'>"            <<  "Benutzername"      <<  "</th>"
            //<<  "<th data-sort='name'>"            <<  "Passwort"          <<  "</th>"
            <<  "<th data-sort='number'>"          <<  "Guthaben"          <<  "</th>"
            <<  "<th data-sort='number'>"          <<  "Admin?"            <<  "</th>"
            <<  "<th data-sort='number'>"          <<  "PermBl?"            <<  "</th>"
            <<  "</tr>"
            <<  "</thead>"
            <<  "<tbody>"
            << endl;

    query.prepare("SELECT id,username,balance,isAdmin,isBlockedPermanently FROM users ORDER BY users.id ASC");
    query.exec();

    int id, isAdmin, isBlockedPermanently;
    double balance;
    string username;
    // string password;

    while(query.next()){
        id          =   query.value(0).toInt();
        username    =   query.value(1).toString().toStdString();
        //password    =   query.value(2).toString().toStdString();
        balance     =   query.value(2).toDouble();
        isAdmin     =   query.value(3).toInt();
        isBlockedPermanently = query.value(4).toInt();

        stream  <<  "<tr>"
                <<  "<td>"      <<  "<input type='checkbox' name='userSelect' id='user"
                <<  id          <<  "' value='"  <<     id          <<  "'>"
                <<  "</td>"
                <<  "<td>"      <<  id           <<    "</td>"
                <<  "<td>"      <<  username     <<    "</td>"
                //<<  "<td>"      <<  password     <<    "</td>"
                <<  "<td>"      <<  balance      <<    "</td>"
                <<  "<td>"      <<  isAdmin      <<    "</td>"
                <<  "<td>"      <<  isBlockedPermanently      <<    "</td>"
                <<  "</tr>"
                <<  endl;
    }

    stream  <<   "</tbody>"
            <<   "</table>"
            <<   "<p>"
            <<   "<input type='checkbox' id='userSelect' class='selectAll'>"
            <<   "Alle auswählen </p>"
            <<   endl;

    string s = stream.str();

    // Testfunktion
    // cout    <<  s   <<  endl;

    QString htmlOutput = QString::fromStdString(s);
    return htmlOutput;
}

// Gibt User Admin-Privillegien
// Auswirkung: Zeige Admin-Menüpunkte und Optionen in App
void sqlfunctions::empowerUser(int id){
    QSqlQuery query;
    query.prepare("UPDATE users SET isAdmin=1 WHERE id=:uid");
    query.bindValue(":uid", id);
    query.exec();
}

// Nimmt User Admin-Privillegien
// Auswirkung: Verstecke Admin-Menüpunkte und Optionen in App
void sqlfunctions::disempowerUser(int id){
    QSqlQuery query;
    query.prepare("SELECT isSuperAdmin FROM users WHERE id = :uid");
    query.bindValue(":uid", id);
    query.exec();
    query.next();
    bool isSuperAdmin = query.value(0).toBool();

    if(isSuperAdmin){
        QMessageBox msgBox;
        msgBox.setText("Dieser User ist ein Super-Admin. Diese sind immun.");
        return;
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Yolo, Biatch!");
    }

    query.prepare("UPDATE users SET isAdmin=0 WHERE id=:uid");
    query.bindValue(":uid", id);
    query.exec();
}

// blockt Account temporär
void sqlfunctions::blockAccount(int id, int hours){
    QDateTime blockedUntil = QDateTime::currentDateTime().addSecs(3600*hours);
    QSqlQuery query;
    query.prepare("UPDATE users SET blockedUntil = :blockedUntil WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":blockedUntil", blockedUntil);
    query.exec();

    QMessageBox msgBox;
    msgBox.setText("Der Account mit der id "+QString::number(id)+" wurde für "+ QString::number(hours) +" Stunden geblockt.");
    msgBox.exec();
}

// blockt Account dauerhaft
void sqlfunctions::blockAccountPermanently(int id){
    QSqlQuery query;
    query.prepare("UPDATE users SET isBlockedPermanently = 1 WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    QMessageBox msgBox;
    msgBox.setText("Der Account mit der id "+QString::number(id)+" wurde permanent geblockt.");
    msgBox.exec();
}

// entblockt Account
void sqlfunctions::unblockAccount(int id){
    QDateTime blockedUntil = QDateTime::currentDateTime();
    // temporären Block entfernen
    QSqlQuery query;
    query.prepare("UPDATE users SET blockedUntil = :blockedUntil WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":blockedUntil", blockedUntil);
    query.exec();

    // dauerhaften Block entfernen
    query.prepare("UPDATE users SET isBlockedPermanently = 0 WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    QMessageBox msgBox;
    msgBox.setText("Der Account mit der id "+QString::number(id)+" wurde wieder freigeschaltet.");
    msgBox.exec();
}

// löscht Account
void sqlfunctions::terminateAccount(int id){
    QMessageBox msgBox;
    msgBox.setText("Achtung Account-Terminierung!");
    msgBox.setInformativeText("Wollen Sie diese(n) Account(s) wirklick terminieren? Diese Aktion ist endgültig.");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int answer = msgBox.exec();
    if(answer == QMessageBox::Yes){
        msgBox.setText("Yes was clicked");
        msgBox.exec();
        QSqlQuery query;
        query.prepare("DELETE FROM users WHERE id=:uid");
        query.bindValue(":uid", id);
        query.exec();
    }
    else if(answer == QMessageBox::No){
        msgBox.setText("Nichts ausgeführt.");
        msgBox.exec();
    }
}

// ändert Guthaben eines Accounts

void sqlfunctions::changeBalance(int id, QString mode, double number){

    if(!isLogin){
        QMessageBox msgBox;
        msgBox.setText("Es ist kein User eingeloggt!");
        msgBox.exec();
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT balance FROM users WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();
    query.next();
    double balance = query.value(0).toDouble();

    QMessageBox msgBox;
    if(mode == "add"){
        balance += number;
        msgBox.setText("Ihr Guthaben wurde erfolgreich um "+QString::number(number)+" aufgelden. Es beträgt nun insgesamt "+QString::number(balance)+".");
        msgBox.exec();
        emit balanceChanged(number);
    }
    else if(mode == "set"){
        int oldBalance = balance;
        balance = number;
        msgBox.setText("Ihr Guthaben wurde erfolgreich auf"+QString::number(number)+" aufgeladen.");
        msgBox.exec();
        emit balanceChanged(oldBalance - balance);
    }
    else if(mode == "scale"){
        int oldBalance = balance;
        balance *= number;
        msgBox.setText("Ihr Guthaben wurde erfolgreich um den Faktor"+QString::number(number)+" skaliert. Es beträgt nun insgesamt "+QString::number(balance)+".");
        msgBox.exec();
        emit balanceChanged(oldBalance - balance);
    }

    query.prepare("UPDATE users SET balance=:balance WHERE id=:id");
    query.bindValue(":balance", balance);
    query.bindValue(":id", id);
    query.exec();
}

// Passwort ändern

void sqlfunctions::changePassword(int id, QString mode){
    QString newMode;
    QSqlQuery query;
    if(mode == "request"){
        newMode = "r";
    }
    if(mode == "force"){
        newMode = "f";
    }
    query.prepare("UPDATE users SET changePasswordMode=:mode WHERE id=:id");
    query.bindValue(":id", id);
    query.bindValue(":mode", newMode);
    query.exec();
}

void sqlfunctions::changePassword(int id, QString mode, QString password){
    QString newMode;
    QSqlQuery query;

    if(mode == "set"){
        query.prepare("UPDATE users SET password=:password WHERE id=:id");
        query.bindValue(":id", id);
        query.bindValue(":password", password);
        query.exec();
        newMode = "n";
    }

    query.prepare("UPDATE users SET changePasswordMode=:mode WHERE id=:id");
    query.bindValue(":id", id);
    query.bindValue(":mode", newMode);
    query.exec();
}

bool sqlfunctions::userChangesPassword(int id, QString password, QString passwordRepeated){
    if(password != passwordRepeated){
        QMessageBox msgBox;
        msgBox.setText("Die eingegebenen Passwörter stimmen nicht überein.");
        return false;
    }
    else{
        QSqlQuery query;
        query.prepare("UPDATE users SET password = :password WHERE id = :id");
        query.bindValue(":password", password);
        query.bindValue(":id", id);
        query.exec();
        return true;
    }
}

void sqlfunctions::deleteWareRecord(int id){
    QMessageBox msgBox;
    msgBox.setText("Achtung Waren-Löschung!");
    msgBox.setInformativeText("Wollen Sie diese Waren(n) wirklick löschen? Diese Aktion ist endgültig.");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int answer = msgBox.exec();
    if(answer == QMessageBox::Yes){
        msgBox.setText("Das Produkt wurde erfolgreich gelöscht.");
        msgBox.exec();
        QSqlQuery query;
        query.prepare("DELETE FROM products WHERE id=:id");
        query.bindValue(":id", id);
        query.exec();
    }
    else if(answer == QMessageBox::No){
        msgBox.setText("Aktion vom Benutzer abgebrochen.");
        msgBox.exec();
    }
}

void sqlfunctions::createWareRecord(){
}

void sqlfunctions::changeStock(int id, QString mode, double number){
    QSqlQuery query;
    query.prepare("SELECT stock, title FROM products WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();
    query.next();
    double stock = query.value(0).toDouble();
    QString title = query.value(1).toString();

    QMessageBox msgBox;
    if(mode == "add"){
        stock += number;
        msgBox.setText("Die Menge von "+ title +" wurde um "+QString::number(number)+" erhöht. Es beträgt nun insgesamt "+QString::number(stock)+".");
        msgBox.exec();
        emit stockChanged(number);
    }
    else if(mode == "set"){
        int oldStock = stock;
        stock= number;
        msgBox.setText("Die Menge von "+ title +" wurde auf "+QString::number(number)+" gesetzt.");
        msgBox.exec();
        emit stockChanged(oldStock - stock);
    }
    else if(mode == "scale"){
        int oldStock = stock;
        stock *= number;
        msgBox.setText("Die Menge von"+ title +" wurde um den Faktor "+ QString::number(number)+" skaliert. Er beträgt nun insgesamt "+QString::number(stock)+".");
        msgBox.exec();
        emit stockChanged(oldStock - stock);
    }
}

void sqlfunctions::changeWarePrice(int id, QString mode, double number){
    QSqlQuery query;
    query.prepare("SELECT price, title FROM products WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();
    query.next();
    double price = query.value(0).toDouble();
    QString title = query.value(1).toString();

    QMessageBox msgBox;
    if(mode == "add"){
        price += number;
        msgBox.setText("Der Preis von "+ title +" wurde um "+QString::number(number)+" erhöht. Es beträgt nun insgesamt "+QString::number(price)+".");
        msgBox.exec();
        emit priceChanged(number);
    }
    else if(mode == "set"){
        int oldPrice = price;
        price= number;
        msgBox.setText("Der Preis von "+ title +" wurde auf "+QString::number(number)+" gesetzt.");
        msgBox.exec();
        emit priceChanged(oldPrice - price);
    }
    else if(mode == "scale"){
        int oldPrice = price;
        price *= number;
        msgBox.setText("Der Preis von"+ title +" wurde um den Faktor "+ QString::number(number)+" skaliert. Er beträgt nun insgesamt "+QString::number(price)+".");
        msgBox.exec();
        emit priceChanged(oldPrice - price);
    }
}


double sqlfunctions::getCurrentCartValue(){
    return currentCartValue;
}

bool sqlfunctions::getLogin(){
    return isLogin;
}

bool sqlfunctions::getIsAdminLoggedIn(){
    return isAdminLoggedIn;
}

int sqlfunctions::getUid(){
    return uid;
}

QString sqlfunctions::getUsername(){
    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE id = :uid");
    query.bindValue(":uid", uid);
    query.exec();
    query.next();
    return query.value(0).toString();
}

double sqlfunctions::getBalance(){
    QSqlQuery query;
    query.prepare("SELECT balance FROM users WHERE id =:uid");
    query.bindValue(":uid", uid);
    query.exec();
    query.next();
    return query.value(0).toDouble();
}

bool sqlfunctions::login(QString username, QString password){
    // Timeout bei mehrfach falscher Eingabe
    time_t timeNow = time(0);


    if(allowedAgain > timeNow && badTries > 2){
        time_t difference = allowedAgain - timeNow;
        QMessageBox msgBox;
        msgBox.setText("Zuviele ("+QString::number(badTries)+") Fehlversuche! Sie dürfen sich in "+QString::number(difference)+" Sekunden wieder einloggen.");
        msgBox.exec();
        return false;
    }

    QSqlQuery query;
    // Prüfen, ob Username-Password-Kombination existiert
    query.prepare("SELECT username, isBlockedPermanently, blockedUntil FROM users WHERE password = :password");
    query.bindValue(":password", password);
    bool accountExists = query.exec();
    query.next();
    QString receivedUsername = query.value(0).toString();
    bool isBlockedPermanently = query.value(1).toBool();
    QDateTime blockedUntil = query.value(2).toDateTime();
    if(isBlockedPermanently){
        QMessageBox msgBox;
        msgBox.setText("Ihr Account wurde wegen Verstoßes gegen die AGB dauerhaft geblockt. Falls Sie hier einen Fehler vermuten, kontaktieren Sie bitte den Support!");
        msgBox.exec();
        return false;
    }
    if(blockedUntil >= QDateTime::currentDateTime()){
        QMessageBox msgBox;
        msgBox.setText("Ihr Account ist temporär gebannt. Sie können sich zu folgender Zeit wieder einloggen: "+blockedUntil.toString()+" !");
        msgBox.exec();
        return false;
    }
    bool credentialsMatch = false;
    if(receivedUsername.toStdString() == username.toStdString()){
        credentialsMatch = true;
    }
    else{
       badTries++;
       timeout();
    }
    // Überprüft ob Account existiert, Passwort/Benutzername-Kombination stimmt
    // und ob ein nicht leerer Benutzername eingegeben wurde.
    if(accountExists && credentialsMatch && username.toStdString()!=""){
        query.prepare("SELECT changePasswordMode FROM users WHERE username = :username");
        query.bindValue(":username", username);
        query.exec();
        query.next();
        QString changePasswordMode = query.value(0).toString();
        QMessageBox msgBox;

        // Testfunktion
        // msgBox.setText(changePasswordMode);
        // msgBox.exec();

        if(changePasswordMode.toStdString() != "n"){
            if(changePasswordMode.toStdString() == "f"){
                msgBox.setText("Ändern Sie umgehend Ihr Passwort!");
                msgBox.exec();
            }
            else if(changePasswordMode.toStdString() == "r"){
                msgBox.setText("Ändern Sie bitte Ihr Passwort!");
                msgBox.exec();
            }
        }

        // Member uid für Einkauf setzen
        query.prepare("SELECT id FROM users WHERE username =:username");
        query.bindValue(":username", username);
        if(query.exec()){
            emit userLoggedIn();
            isLogin = true;
        }
        query.next();
        uid = query.value(0).toInt();

        /*// Testfunktion
        QMessageBox msgBox;
        msgBox.setText("Der eingeloggte User hat die ID "+QString::number(uid)+".");
        msgBox.exec();*/

        // Prüfen ob ein Admin eingeloggt ist
        // Setze entsprechend isAdminLoggedIn auf true bzw. false
        // Wenn ja sende Signal adminLoggedIn aus
        // Gib Admin-Rechte.

        query.prepare("SELECT isAdmin FROM users WHERE id = :uid");
        query.bindValue(":uid", uid);
        query.exec();
        query.next();
        bool userIsAdmin = query.value(0).toBool();
        if(userIsAdmin){
            emit adminLoggedIn();
            isAdminLoggedIn = true;
            /* // Testfunktion
            QMessageBox msgBox;
            msgBox.setText("User als Admin erkannt. Das Admin-Flag ist auf "+QString::number(isAdminLoggedIn)+".");
            msgBox.exec();*/
        }
        else{
            /* // Testfunktion
            QMessageBox msgBox;
            msgBox.setText("User als Kunde erkannt. Das Admin-Flag ist auf "+QString::number(isAdminLoggedIn)+".");
            msgBox.exec();
            */
        }

        return true;
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Benutzername oder Passwort inkorrekt!");
        msgBox.exec();
        return false;
    }
}

// Login-Strafe ausrechnen
void sqlfunctions::timeout(){
    allowedAgain = 30*(badTries-2) + time(0);
}

// User ausloggen
bool sqlfunctions::logout(){
    /* USER FRAGEN, OB ER SICH WIRKLICH AUSLOGGEN WILL, DA SEIN WARENKORB GELÖSCHT WIRD!
    bool areYouSure = false;
    QMessageBox msgBox;
    QAbstractButton button;
    msgBox.addButton(button, );
    msgBox.setText("Logout vom User abgebrochen.");
    msgBox.exec();

    if(!areYouSure){
        msgBox.setText("Logout vom User abgebrochen.");
        msgBox.exec();
        return false;
    }
    */

    // Auslog-Funktionalität
    isLogin = false;
    isAdminLoggedIn = false;
    uid = -1;
    clearCart();
    emit userLoggedOut();

    QMessageBox msgBox;
    msgBox.setText("Logout erfolgreich!");
    msgBox.exec();
    return true;
}

// ----------------------------------------------------------------------------------
// -----------------------------------------TEST-------------------------------------
// ----------------------------------------------------------------------------------

void sqlfunctions::testJs(){
    QMessageBox msgBox;
    msgBox.setText(listAllProducts());
    msgBox.exec();
}

void sqlfunctions::testCpp(){
    QMessageBox msgBox;
    msgBox.setText("Dieser Code wurde ausgeführt!");
    msgBox.exec();
}

void sqlfunctions::testCpp2(){
    QMessageBox msgBox;
    msgBox.setText("Dieser andere Code wurde ausgeführt!");
    msgBox.exec();
}

void sqlfunctions::testSql(QString a, QString b, QString c){
    QMessageBox msgBox;
    msgBox.setText("Erstes Argument: "+a +"\nZweites Argument: "+b + "\nDrittes Argument: "+c);
    msgBox.exec();
}

// ----------------------------------------------------------------------------------
// ---------------------------------------SIGNALE------------------------------------
// ----------------------------------------------------------------------------------
/*
void sqlfunctions::cartChanged(){
    return;
}
*/
