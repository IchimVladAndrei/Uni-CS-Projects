from src.domain.entities import Validate
from src.repository.bin_repo import BinaryRepository
from src.repository.file_repo import FileRepository
from src.repository.repo import Repository
from src.services.service import ServiceBook
from src.ui.console import Console

if __name__ == '__main__':
    val = Validate()
    # repo=Repository(val)
    # repo = BinaryRepository("books.pickle", val)
    repo=FileRepository("books.txt",val)
    s = ServiceBook(repo)
    console = Console(s)
    console.solve()
