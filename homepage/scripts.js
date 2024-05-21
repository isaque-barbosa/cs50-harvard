document.addEventListener('DOMContentLoaded', function() {
    fetch('./pages/home.html')
          .then(response => response.text())
          .then(data => {
              document.getElementById('mainContent').innerHTML = data;
          })
          .catch(error => console.error(error));
    init()
  });

function init() {
    document.getElementById('homeBtn').addEventListener('click', function() {
        fetch('./pages/home.html')
            .then(response => response.text())
            .then(data => {
                document.getElementById('mainContent').innerHTML = data;
                updateActiveMenu('homeBtn');
            })
            .catch(error => console.error(error));
    });

    document.getElementById('aboutBtn').addEventListener('click', function() {
        fetch('./pages/about.html')
            .then(response => response.text())
            .then(data => {
                document.getElementById('mainContent').innerHTML = data;
                updateActiveMenu('aboutBtn');
            })
            .catch(error => console.error(error));
    });

    document.getElementById('moreBtn').addEventListener('click', function() {
        fetch('./pages/more.html')
            .then(response => response.text())
            .then(data => {
                document.getElementById('mainContent').innerHTML = data;
                updateActiveMenu('moreBtn');
            })
            .catch(error => console.error(error));
    });
}

function updateActiveMenu(idMenu) {
    var elements = document.querySelectorAll('.active');
    elements.forEach(function(element) {
        element.classList.remove('active');
    });
    let current = document.getElementById(idMenu);
    current.classList.add('active');
}
