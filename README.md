# soccer-common
This repositiory contains classes and methods that can be used by ssl, vss or any other category of robot soccer that allows the same architecture

COMPILER TIME x RUN TIME

RUN QMAKE - LEMBRAR

Mixin

https://www.qtcentre.org/threads/11190-QThread-and-Multiple-inheritance

https://stackoverflow.com/questions/5368258/the-copy-constructor-and-assignment-operator

https://stackoverflow.com/questions/5116756/difference-between-pointer-and-reference-as-thread-parameter

cuidado com a copia de classes que contem pointeiros

https://en.cppreference.com/w/cpp/language/copy_assignment

https://stackoverflow.com/questions/4617167/static-member-functions-and-thread-safety

https://www.embedded.com/how-to-make-c-more-real-time-friendly/

https://stackoverflow.com/questions/27993819/hashmap-vs-switch-statement-performance/27993932

bool insertAsGroupBox(const QString &_name, const QJsonObject &_object) {
  if (json.contains(_name)) {
    return false;
  }

}

https://doc.qt.io/qt-5/signalsandslots.html

AVOIDING WARNINGS c++17
INLINE INIT c++17

- 00) astyle config
- 01) create a wiki
- 02) set commit patterns
- 03) set modules
- 04) set threads
- 05) set Qt preferences
- 06) parameters as json

https://stackoverflow.com/questions/6602036/qvector-vs-qlist

// https://www.kdab.com/wp-content/uploads/stories/slides/Day2/OliverGoffart_lockfree_0.pdf
// https://stackoverflow.com/questions/50601726/is-it-ok-to-use-stdatomic-with-a-struct-that-is-pod-except-that-it-has-a-const
// https://baptiste-wicht.com/posts/2012/07/c11-concurrency-tutorial-part-4-atomic-type.html
// https://stackoverflow.com/questions/31978324/what-exactly-is-stdatomic
// https://stackoverflow.com/questions/13299299/shared-variable-among-classes-c
// https://stackoverflow.com/questions/32833786/is-there-any-difference-between-mutex-and-atomic-operation/32835331

/*
usar qdebug // overload de todas as q classes, buffer na qstring

*/

// about cache
// https://www.aristeia.com/TalkNotes/ACCU2011_CPUCaches.pdf


// https://woboq.com/blog/qmap_qhash_benchmark.html

QMap<QString, std::function<Vision*(QJson &json)>> map;

map["Vision"] = [&](QJson &json) {
  return new VevaVision(json);
};
