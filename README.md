# soccer-common
This repositiory contains classes and methods that can be used by ssl, vss or any other category of robot soccer that allows the same architecture

--------------------
Warthogs:
https://warthog.assembla.com/wiki/show/warthog-dia/WRCoach_v1
https://warthog.assembla.com/wiki/show/warthog-dia/WRCoach_v2

--------------------
https://doc.qt.io/archives/qt-4.8/threads-qobject.html

https://doc.qt.io/archives/qq/qq10-signalmapper.html

Common {
  description: Concentrates everything that can be shared in different categories of robot soccer;

  Modules {
    description: Can be an inheritance from a QThread, with another member functions that facilitates the creation of tabs to interface independently, informs the parameters that can be modified, obtaining the logger for each module, and rules for the generated packages and for the modules themselves;
  }

  Packages {
    description: As an abstract class, it can provide methods that facilitate the creation of loggers and have standards for inherited packages and communication between different computers;
  }

  Utils {
    description: The current utils, with generalization in the methods;
  }

  Skills {
    description: If there is a common entity within the categories, we can have a library of skills:
      - followBall(...);
      - passTheBall(...);
      - markTheEnemyAlone(...);
      ...
      If we make a specification of the robots, for example:
        Robot -> KickerRobot
      It will be possible to use only the methods that that robot has;
  }
  
  Plannings {
    description: Saves all planning algorithms;
    input: Most cases need to be analyzed in order to obtain common inputs and outputs. some of them need to run in parallel, how to proceed?;
    output: -
  }

  Navigations {
    description: Saves all navigation algorithms;
    input: Most cases need to be analyzed in order to obtain common inputs and outputs;
    output: -
  }
}

UserInterface {
  description: Interprets each module to display to the user, receives the variables that can be set from the modules, presents a game viewer, and more;
}

LoggerInterpreter {
  description: Logger interpretation software. It could work as a video player, where is possible to configure what will be displayed;
  
  LoggerModule {
    description: It can be a module that receives the information from the other modules and saves it in parallel to csv files for analysis in another program;
    input:
    output:
  }
}

SSL-Vision {
  description: Must be another software. It should deliver already formatted packages;
  input: Environment variables;
  output: VisionPackage;
  
  VisionModule {
    description:
    input:
    output:
  }
}

SSL-Simulation {
  description: Must be another software. It should deliver already formatted packages;
  input: Environment variables;
  output: SimulationPackage;
  
  SimulationModule {
    description:
    input:
    output:
  }
}

VisionProcessingModule {
  description: I think that module can be generic, because if we have common packages, we can process in the same way. Kalman filter, and more. It is important to know what filters will belong to the camera software (if the camera union will be implemented in SSL-Vision or here, in this case). If the input is a SimulationPackage, we can just foward, for example.
  input: UserInterface, VisionPackage or SimulationPackage;
  output: ProcessedVisionPackage;
}

SSL-AutoReferee {
  description: Must be another software. It should deliver already formatted packages;
  input: Environment variables;
  output: RefereePackage;
  
  AutoRefereeModule {
    
  }
}

SSL-Referee-Box {
  description: Must be another software. It should deliver already formatted packages;
  input: Environment variables;
  output: RefereePackage;
}

CommunicationModule {
  description: 
  input: 
  output: 
}

O SSL poderia ser visto como:

SSL {
  Common @ 00001;
  
  UserInterface @ 00001;
  
  SSL-Vision @ 00001;

  SSL-Simulation @ 00001;
  
  VisionProcessingModule @ 00001;
  
  SSL-AutoReferee @ 00001;
  
  SSL-Referee-Box @ 00001;
  
  Communication @ 00001;
  
  Local {
    ...
  }
}


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
